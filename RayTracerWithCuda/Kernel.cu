
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <math.h>
#include <stdio.h>

__device__ unsigned short RD(int i, int j, int W, int H) {
#define D(x) (x-W/2.)/(W/2.)
	float x = D(i), y = D(j), X, Y, n = 0; while (n++<200 && (X = x*x) + (Y = y*y)<4) { x = X - Y + .36237; y = 2 * x*y + .32; }return log(n) * 256;
}

__device__ unsigned short GR(int i, int j, int W, int H) {
	float x = D(i), y = D(j), X, Y, n = 0; while (n++<200 && (x*x + y*y)<4) { X = x; Y = y; x = X*X - Y*Y + -.7; y = 2 * X*Y + .27015; }return log(n) * 128;
}

__device__ unsigned short BL(int i, int j, int W, int H) {
	float x = D(i), y = D(j), X, Y, n = 0; while (n++<600 && (x*x + y*y)<4) { X = x; Y = y; x = X*X - Y*Y + .36237; y = 2 * X*Y + .32; }return log(n) * 128;
}

__global__ void RGBKernel(float* R, float* G, float* B, int W, int H)
{
	int x = blockIdx.x;
	int y = threadIdx.x;

	R[x * W + y] = RD(x, y, W, H) / 255.0f;
	G[x * W + y] = GR(x, y, W, H) / 255.0f;
	B[x * W + y] = BL(x, y, W, H) / 255.0f;
}

extern "C" cudaError_t cuadRGB(int W, int H, float* R, float* G, float* B)
{
	float* DevR;
	float* DevG;
	float* DevB;

	auto cudaStatus = cudaSetDevice(0);
	if (cudaStatus != cudaSuccess) 
	{
		fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
		goto Error;
	}

	cudaStatus = cudaMalloc((void**)(&DevR), sizeof(float) * W * H);
	if (cudaStatus != cudaSuccess) 
	{
		fprintf(stderr, "cudaMalloc failed!");
		goto Error;
	}

	cudaStatus = cudaMalloc((void**)(&DevG), sizeof(float) * W * H);
	if (cudaStatus != cudaSuccess) 
	{
		fprintf(stderr, "cudaMalloc failed!");
		goto Error;
	}

	cudaStatus = cudaMalloc((void**)(&DevB), sizeof(float) * W * H);
	if (cudaStatus != cudaSuccess) 
	{
		fprintf(stderr, "cudaMalloc failed!");
		goto Error;
	}

	RGBKernel<<<W, H>>> (DevR, DevG, DevB, W, H);

	cudaStatus = cudaGetLastError();
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "addKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
		goto Error;
	}

	cudaStatus = cudaDeviceSynchronize();
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching addKernel!\n", cudaStatus);
		goto Error;
	}

	cudaStatus = cudaMemcpy(R, DevR, sizeof(float) * W * H, cudaMemcpyDeviceToHost);
	if (cudaStatus != cudaSuccess) 
	{
		fprintf(stderr, "cudaMemcpy failed!");
		goto Error;
	}

	cudaStatus = cudaMemcpy(G, DevG, sizeof(float) * W * H, cudaMemcpyDeviceToHost);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMemcpy failed!");
		goto Error;
	}

	cudaStatus = cudaMemcpy(B, DevB, sizeof(float) * W * H, cudaMemcpyDeviceToHost);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMemcpy failed!");
		goto Error;
	}

Error:
	cudaFree(DevR);
	cudaFree(DevG);
	cudaFree(DevB);

	return cudaStatus;
}
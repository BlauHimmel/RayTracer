#include "stdafx.h"

#include "Math\Matrix\Matrix4f.h"
#include "Math\Vector\Vector2f.h"
#include "Math\Vector\Vector3f.h"
#include "Math\Vector\Vector4f.h"
#include "Container\List\Array.hpp"
#include "Container\List\ArrayList.hpp"
#include "Container\List\LinkedList.hpp"
#include "Container\List\PriorityQueue.hpp"
#include "Container\List\Queue.hpp"
#include "Container\List\Stack.hpp"
#include "Container\Map\HashMap.hpp"
#include "Container\Map\TreeMap.hpp"
#include "Container\Set\HashSet.hpp"
#include "Container\Set\TreeSet.hpp"
#include "Math\Common\MathFunction.hpp"
#include "Tools\Image\Bitmap.h"
#include "Tools\UI\Window.h"
#include "Raytracer\Light\ILight.h"
#include "RayTracer\Camera\ICamera.h"
#include "RayTracer\Camera\OrthographicCamera.h"
#include "RayTracer\Camera\PerspectiveCamera.h"
#include "RayTracer\Scene.h"
#include "RayTracer\Tracer\RayTracing.h"
#include "Tools\Json\json.hpp"

#include <cuda_runtime.h>
#include <device_launch_parameters.h>

int W = 1024;
int H = W;

extern "C" cudaError_t cuadRGB(int W, int H, float* R, float* G, float* B);

int main()
{
	auto Scene = std::make_shared<EasyRayTracer::Scene>("Scene\\ReflectionScene.json");
	auto RayCasting = std::make_shared<EasyRayTracer::RayTracing>(Scene, 5);
	auto Camera = Scene->GetCamera();
	
	EasyTools::Bitmap Image(W, H);
	EasyContainer::Array<EasyMath::Color> Pixels(W * H);

	float LastPercent = 0.0f;
	float Percent = 0.0f;

	for (auto j = 0; j < H; j++)
	{
		for (auto i = 0; i < W; i++)
		{
			float X = static_cast<float>(i) * 2.0f / W - 1.0f;
			float Y = static_cast<float>(j) * 2.0f / H - 1.0f;
			float TMin = 0.05f;

			EasyRayTracer::Ray PrimaryRay = Camera->GenerateRay(EasyMath::Vector2f(X, Y));
			auto Color = RayCasting->Trace(PrimaryRay, TMin, 1, 1.0f);

			Pixels[j * W + i] = Color;

			Percent = static_cast<float>(j * W + i) / static_cast<float>(W * H);
			if (Percent - LastPercent > 0.01f)
			{
				LastPercent = Percent;
				std::cout << Percent << std::endl;
			}
		}
	}

	Image.SetPixel(Pixels);
	Image.Save("Image.bmp");
	
	std::function<void(String&)> Callback = [](String& String)
	{
		PRINTF("Cmd : %s\n", String.c_str());
	};

	WINDOW_CREATE(W, H, "Test", "Output");
	WINDOW_MAINLOOP_BEGIN(Callback)
		WINDOW_UPDATE_PIXELS(Pixels);
		WINDOW_UPDATE_FLAG(false);
	WINDOW_MAINLOOP_END()



	return 0;
}
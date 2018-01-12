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
#include "RayTracer\Material\CookTorranceMaterial.h"
#include "Tools\Json\json.hpp"

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

int W = 1024;
int H = W;

extern "C" cudaError_t cuadRGB(int W, int H, float* R, float* G, float* B);

int main()
{
	//EasyMath::Matrix4f m(1.0f, 1.1f, 1.2f, 1.3f, 1.41122341121111f, 1.5f, 1.6f, 1.7f, 1.8f, 1.9f, 2.0f, 2.1f, 2.2f, 2.3f, 2.4f, 2.5f);
	//EasyMath::Vector2f v2;
	//EasyMath::Vector2f v22;
	//EasyMath::Vector3f v3;
	//EasyMath::Vector4f v4(1.222f, 2.556f, 8.13f, 0.1111111564f);

	//EasyContainer::Array<int> a(4);
	//EasyContainer::ArrayList<int> al = { 1,2,3,4 };
	//EasyContainer::LinkedList<int> ll = { 1,2,3,4 };
	//EasyContainer::PriorityQueue<int, false> pqf;
	//EasyContainer::PriorityQueue<int, true> pqt;
	//EasyContainer::Queue<int> q;
	//EasyContainer::Stack<int> s;
	//EasyContainer::TreeMap<int, int> tm;
	//EasyContainer::HashMap<int, int> hm;
	//EasyContainer::TreeSet<int> ts;
	//EasyContainer::HashSet<int> hs;

	//EasyContainer::LinkedList<int> ll2 = ll;
	//ll2.Reverse();
	//ll2.Reverse(1, 3);
	//ll2.Contains(9);
	//std::unique_ptr<EasyContainer::LinkedList<int>> tmp1 = ll2.Find(
	//LIST_FILTER
	//{
	//	return Element % 2 == 0;
	//}
	//);
	//ll2.InsertRange(1, { 9,9,9 });
	//ll2.LastIndexOf(9);
	//ll2.Sort();
	//ll2.LastIndexOf(9);
	//ll2.RemoveAt(3);
	//ll2.Remove(9);

	//EasyContainer::ArrayList<int> al2 = al;
	//al2.Reverse();
	//al2.Reverse(1, 3);
	//al2.Contains(9);
	//al2.Contains(9);
	//std::unique_ptr<EasyContainer::ArrayList<int>> tmp2 = al2.Find(
	//LIST_FILTER
	//{
	//	return Element % 2 == 0;
	//}
	//);
	//al2.InsertRange(1, { 9,9,9 });
	//al2.LastIndexOf(9);
	//al2.Sort();
	//al2.LastIndexOf(9);
	//al2.RemoveAt(3);
	//al2.Remove(9);

	//EasyContainer::Stack<int> s1;
	//EasyContainer::Stack<int> s2;

	//s1.Push(1);
	//s1.Push(2);
	//s1.Push(3);

	//s2 = s1;

	//EasyContainer::Queue<int> q1;
	//EasyContainer::Queue<int> q2;

	//q1.Push(1);
	//q1.Push(2);
	//q1.Push(3);

	//q2 = q1;

	//EasyContainer::HashMap<int, int> hs1;
	//EasyContainer::HashMap<int, int> hs2;

	//hs1[1] = 111;
	//hs1[2] = 222;
	//hs1[3] = 333;

	//hs2 = hs1;

	//EasyContainer::LinkedList<int> lll1 = { 1, 3, 5, 7 };
	//EasyContainer::LinkedList<int> lll2;
	//lll2 = lll1;

	//EasyContainer::ArrayList<int> all1 = { 1, 3, 5, 7 };
	//EasyContainer::ArrayList<int> all2;
	//all2 = all1;

	EasyTools::Bitmap bits(W, H);
	EasyContainer::Array<EasyMath::Color> Pixels(W * H);

	std::unique_ptr<float[]> R(new float[W * H]);
	std::unique_ptr<float[]> G(new float[W * H]);
	std::unique_ptr<float[]> B(new float[W * H]);

	cuadRGB(W, H, R.get(), G.get(), B.get());
	for (auto i = 0; i < W; i++)
	{
		for (auto j = 0; j < H; j++)
		{
			Pixels[i * W + j].R() = R[i * W + j];
			Pixels[i * W + j].G() = G[i * W + j];
			Pixels[i * W + j].B() = B[i * W + j];
		}
	}

	bits.SetPixel(Pixels);
	bits.Save("Image.bmp");

	std::function<void(String&)> Callback = [](String& String)
	{
		PRINTF("Cmd : %s\n", String.c_str());
	};

	WINDOW_CREATE(W, H, "Test", "Output");
	WINDOW_MAINLOOP_BEGIN(Callback)
		WINDOW_UPDATE_PIXELS(Pixels);
		WINDOW_UPDATE_FLAG(true);
	WINDOW_MAINLOOP_END()

	return 0;
}

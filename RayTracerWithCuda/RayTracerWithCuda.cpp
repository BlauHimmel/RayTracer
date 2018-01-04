#include "stdafx.h"

#include "Matrix4f.h"
#include "Vector2f.h"
#include "Vector3f.h"
#include "Vector4f.h"
#include "Array.hpp"
#include "ArrayList.hpp"
#include "LinkedList.hpp"
#include "PriorityQueue.hpp"
#include "Queue.hpp"
#include "Stack.hpp"
#include "HashMap.hpp"
#include "TreeMap.hpp"
#include "HashSet.hpp"
#include "TreeSet.hpp"
#include "MathFunction.hpp"
#include "Bitmap.h"
#include "Window.h"
#include "ILight.h"

int main()
{
	EasyMath::Matrix4f m(1.0f, 1.1f, 1.2f, 1.3f, 1.41122341121111f, 1.5f, 1.6f, 1.7f, 1.8f, 1.9f, 2.0f, 2.1f, 2.2f, 2.3f, 2.4f, 2.5f);
	EasyMath::Vector2f v2;
	EasyMath::Vector2f v22;
	EasyMath::Vector3f v3;
	EasyMath::Vector4f v4(1.222f, 2.556f, 8.13f, 0.1111111564f);

	EasyContainer::Array<int> a(4);
	EasyContainer::ArrayList<int> al = { 1,2,3,4 };
	EasyContainer::LinkedList<int> ll = { 1,2,3,4 };
	EasyContainer::PriorityQueue<int, false> pqf;
	EasyContainer::PriorityQueue<int, true> pqt;
	EasyContainer::Queue<int> q;
	EasyContainer::Stack<int> s;
	EasyContainer::TreeMap<int, int> tm;
	EasyContainer::HashMap<int, int> hm;
	EasyContainer::TreeSet<int> ts;
	EasyContainer::HashSet<int> hs;

	EasyContainer::LinkedList<int> ll2 = ll;
	ll2.Reverse();
	ll2.Reverse(1, 3);
	ll2.Contains(9);
	std::unique_ptr<EasyContainer::LinkedList<int>> tmp1 = ll2.Find(
	LIST_FILTER
	{
		return Element % 2 == 0;
	}
	);
	ll2.InsertRange(1, { 9,9,9 });
	ll2.LastIndexOf(9);
	ll2.Sort();
	ll2.LastIndexOf(9);
	ll2.RemoveAt(3);
	ll2.Remove(9);

	EasyContainer::ArrayList<int> al2 = al;
	al2.Reverse();
	al2.Reverse(1, 3);
	al2.Contains(9);
	al2.Contains(9);
	std::unique_ptr<EasyContainer::ArrayList<int>> tmp2 = al2.Find(
	LIST_FILTER
	{
		return Element % 2 == 0;
	}
	);
	al2.InsertRange(1, { 9,9,9 });
	al2.LastIndexOf(9);
	al2.Sort();
	al2.LastIndexOf(9);
	al2.RemoveAt(3);
	al2.Remove(9);

	EasyContainer::Stack<int> s1;
	EasyContainer::Stack<int> s2;

	s1.Push(1);
	s1.Push(2);
	s1.Push(3);

	s2 = s1;

	EasyContainer::Queue<int> q1;
	EasyContainer::Queue<int> q2;

	q1.Push(1);
	q1.Push(2);
	q1.Push(3);

	q2 = q1;

	EasyContainer::HashMap<int, int> hs1;
	EasyContainer::HashMap<int, int> hs2;

	hs1[1] = 111;
	hs1[2] = 222;
	hs1[3] = 333;

	hs2 = hs1;

	EasyContainer::LinkedList<int> lll1 = { 1, 3, 5, 7 };
	EasyContainer::LinkedList<int> lll2;
	lll2 = lll1;

	EasyContainer::ArrayList<int> all1 = { 1, 3, 5, 7 };
	EasyContainer::ArrayList<int> all2;
	all2 = all1;

	EasyTools::Bitmap bits(200, 200);
	EasyContainer::Array<uint8> reds(40000);

	for (auto i = 0; i < reds.Length(); i++)
	{
		if (i < 100)
			reds[i] = 255;
		else
			reds[i] = 125;
	}

	bits.SetBlueChannel(reds);
	bits.Save("Red.bmp");

	EasyContainer::Array<EasyMath::Color> reds2(40000);

	EasyMath::Color c1 = EasyMath::Color(255, 0, 0);
	EasyMath::Color c2 = EasyMath::Color(125, 0, 0);

	for (int i = 0; i < 40000; i++)
	{
		if (i < 100)
			reds2[i] = c1;
		else
			reds2[i] = c2;
	}
	
	std::function<void(String&)> Callback = [](String& String)
	{
		PRINTF("Cmd : %s\n", String.c_str());
	};

	WINDOW_CREATE(200, 200, "≤‚ ‘Test", "Output");
	WINDOW_MAINLOOP_BEGIN(Callback)
		WINDOW_UPDATE_PIXELS(reds2);
		WINDOW_UPDATE_FLAG(false);
	WINDOW_MAINLOOP_END()
		
	return 0;
}

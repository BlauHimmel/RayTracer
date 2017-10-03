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

int main()
{

	EasyMath::Matrix4f m(1.0f, 1.1f, 1.2f, 1.3f, 1.41122341121111f, 1.5f, 1.6f, 1.7f, 1.8f, 1.9f, 2.0f, 2.1f, 2.2f, 2.3f, 2.4f, 2.5f);
	EasyMath::Vector2f v2;
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

	std::cout << v2 << std::endl;
	std::cout << v3 << std::endl;
	std::cout << v4 << std::endl;
	std::cout << m << std::endl;

	EasyContainer::LinkedList<int> ll2 = ll;
	ll2.Reverse();
	ll2.Reverse(1, 3);
	ll2.Contains(9);
	EasyContainer::LinkedList<int> tmp1 = ll2.Find(
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
	EasyContainer::ArrayList<int>tmp2 = al2.Find(
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

	EasyTools::Bitmap bit("1.bmp");
	if (bit.IsValid())
	{
		bit.Save("2.bmp");
	}

	return 0;
}


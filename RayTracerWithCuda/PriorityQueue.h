#pragma once

#include "TemplateDependency.h"
#include "TemplateMacro.h"

namespace EasyTemplate
{

	template<typename TElement, bool IsMaxHeap>
	class PriorityQueue{};

	template<typename TElement>
	class PriorityQueue<TElement, true>
	{

	private:

		std::priority_queue<TElement> m_Queue;

	public:

		PriorityQueue() : m_Queue() {};

	public:

		void Push(TElement Element) { m_Queue.push(Element); };
		void Pop() { m_Queue.pop(); };
		TElement Top() { return m_Queue.top(); };
		int Size() const { return m_Queue.size(); };
		bool Empty() const { return m_Queue.empty(); };

	};

	template<typename TElement>
	class PriorityQueue<TElement, false>
	{

	private:

		std::priority_queue<TElement, std::vector<TElement>, std::greater<TElement>> m_Queue;

	public:

		PriorityQueue() : m_Queue() {};

	public:

		void Push(TElement Element) { m_Queue.push(Element); };
		void Pop() { m_Queue.pop(); };
		TElement Top() { return m_Queue.top(); };
		int Size() const { return m_Queue.size(); };
		bool Empty() const { return m_Queue.empty(); };

	};
}
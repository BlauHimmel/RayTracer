#pragma once

#include "TemplateDependency.h"
#include "TemplateMacro.h"

namespace EasyTemplate
{

	template<typename TElement>
	class Queue
	{

	private:

		std::queue<TElement> m_Queue;
		
	public:

		Queue();

	public:

		void Push(TElement Element);
		void Pop();
		TElement Front();
		Int32 Size() const;
		bool Empty() const;

	};

	template<typename TElement>
	inline Queue<TElement>::Queue() : m_Queue()
	{
	
	}

	template<typename TElement>
	inline void Queue<TElement>::Push(TElement Element)
	{
		m_Queue.push(Element);
	}

	template<typename TElement>
	inline void Queue<TElement>::Pop()
	{
		m_Queue.pop();
	}

	template<typename TElement>
	inline TElement Queue<TElement>::Front()
	{
		return m_Queue.front();
	}

	template<typename TElement>
	inline Int32 Queue<TElement>::Size() const
	{
		return m_Queue.size();
	}

	template<typename TElement>
	inline bool Queue<TElement>::Empty() const
	{
		return m_Queue.empty();
	}

}
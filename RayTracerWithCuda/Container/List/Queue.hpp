#pragma once

#ifndef __QUEUE__
#define __QUEUE__

#include "Container\Dependency\ContainerDependency.h"
#include "Container\Dependency\ContainerMacro.h"

namespace EasyContainer
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
		int32 Size() const;
		bool Empty() const;

	};

	template<typename TElement>
	INLINE Queue<TElement>::Queue() : m_Queue()
	{
	
	}

	template<typename TElement>
	INLINE void Queue<TElement>::Push(TElement Element)
	{
		m_Queue.push(Element);
	}

	template<typename TElement>
	INLINE void Queue<TElement>::Pop()
	{
		m_Queue.pop();
	}

	template<typename TElement>
	INLINE TElement Queue<TElement>::Front()
	{
		return m_Queue.front();
	}

	template<typename TElement>
	INLINE int32 Queue<TElement>::Size() const
	{
		return static_cast<int32>(m_Queue.size());
	}

	template<typename TElement>
	INLINE bool Queue<TElement>::Empty() const
	{
		return m_Queue.empty();
	}

}

#endif
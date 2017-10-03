#pragma once

#include "ContainerDependency.h"
#include "ContainerMacro.h"

namespace EasyContainer
{

	template<typename TElement>
	class Stack
	{

	private:

		std::stack<TElement> m_Stack;

	public:

		Stack();

	public:

		void Push(TElement& Element);
		void Pop();
		TElement Top() const;
		int32 Size() const;
		bool Empty() const;

	};

	template<typename TElement>
	inline Stack<TElement>::Stack() : m_Stack()
	{
	
	}

	template<typename TElement>
	inline void Stack<TElement>::Push(TElement& Element)
	{
		m_Stack.push(Element);
	}

	template<typename TElement>
	inline void Stack<TElement>::Pop()
	{
		m_Stack.pop();
	}

	template<typename TElement>
	inline TElement Stack<TElement>::Top() const
	{
		return m_Stack.top();
	}

	template<typename TElement>
	inline int32 Stack<TElement>::Size() const
	{
		return m_Stack.size();
	}

	template<typename TElement>
	inline bool Stack<TElement>::Empty() const
	{
		return m_Stack.empty();
	}

}
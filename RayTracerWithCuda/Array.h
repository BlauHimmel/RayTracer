#pragma once

#include "TemplateDependency.h"
#include "TemplateMacro.h"
#include "GlobalDependency.h"
#include "GlobalMacro.h"

namespace EasyTemplate
{

	template<typename TElement>
	class Array
	{

		template<typename TElement> friend class Array;

	public:

		using ArrayInitializer = std::initializer_list<TElement>;

	private:

		TElement* m_Datas;
		int m_Length;

	public:

		Array(int Length);
		Array(TElement* Data, int Length);
		Array(ArrayInitializer Initializer);
		Array(Array<TElement>& Other);
		~Array();

	public:

		TElement& operator[](int Index);
		int Length() const;

	public:

		decltype(auto) begin();
		decltype(auto) end();

	};

	template<typename TElement>
	inline Array<TElement>::Array(int Length)
	{
		m_Datas = new TElement[Length];
		if (m_Datas == nullptr)
		{
			DEBUG_ERROR("Array Memory Allocate Failure");
		}

		memset(m_Datas, 0, Length * sizeof(TElement));
		m_Length = Length;
	}

	template<typename TElement>
	inline Array<TElement>::Array(TElement* Data, int Length)
	{
		m_Length = Length;
		m_Datas = new TElement[m_Length];
		if (m_Datas == nullptr)
		{
			DEBUG_ERROR("Array Memory Allocate Failure");
		}

		for (auto i = 0; i < Length; i++)
		{
			m_Datas[i] = Data[i];
		}
	}

	template<typename TElement>
	inline Array<TElement>::Array(ArrayInitializer Initializer)
	{
		m_Length = Initializer.size();
		m_Datas = new TElement[m_Length];
		if (m_Datas == nullptr)
		{
			DEBUG_ERROR("Array Memory Allocate Failure");
		}

		int Index = 0;
		for (auto Element : Initializer)
		{
			m_Datas[Index] = Element;
			Index++;
		}
	}

	template<typename TElement>
	inline Array<TElement>::Array(Array<TElement>& Other)
	{
		m_Datas = new TElement[Other.m_Length];
		m_Length = Other.m_Length;
		for (int i = 0; i < m_Length; i++)
		{
			m_Datas[i] = Other.m_Datas[i];
		}
	}

	template<typename TElement>
	inline Array<TElement>::~Array()
	{
		delete[] m_Datas;
		m_Datas = nullptr;
	}

	template<typename TElement>
	inline TElement& Array<TElement>::operator[](int Index)
	{
		if (Index >= m_Length || Index < 0)
		{
			DEBUG_ERROR("Array Index Out Of Range");
		}
		return m_Datas[Index];
	}

	template<typename TElement>
	inline int Array<TElement>::Length() const
	{
		return m_Length;
	}

	template<typename TElement>
	inline decltype(auto) Array<TElement>::begin()
	{
		return m_Datas;
	}

	template<typename TElement>
	inline decltype(auto) Array<TElement>::end()
	{
		return m_Datas + m_Length;
	}
}
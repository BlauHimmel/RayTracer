#pragma once

#include "TemplateDependency.h"
#include "TemplateMacro.h"
#include "GlobalDependency.h"
#include "GlobalMacro.h"

namespace EasyTemplate
{

	template<typename TElement>
	class LinkedList
	{

	public:

		using ListInitializer = std::initializer_list<TElement>;
		using ListDelegate = std::function<void(TElement)>;
		using ListFilter = std::function<bool(TElement)>;

	private:

		std::list<TElement> m_List;

	public:

		LinkedList();
		LinkedList(int Capacity);
		LinkedList(int Capacity, TElement Value);
		LinkedList(ListInitializer Initializer);
		LinkedList(LinkedList<TElement>& Other);
		LinkedList(LinkedList<TElement>&& Other);

	public:

		TElement& operator[](int Index);
		void Add(TElement Element);
		void Add(const LinkedList<TElement>& Collection);
		bool Contains(TElement Element) const;
		int IndexOf(TElement Element) const;
		int LastIndexOf(TElement Element) const;
		void Insert(int Index, TElement Element);
		void InsertRange(int Index, const LinkedList<TElement>& Collection);
		void Reverse();
		void Reverse(int BeginIndex, int EndIndex);
		LinkedList<TElement> Find(ListFilter Filter) const;
		int Remove(TElement Element);
		int Remove(ListFilter Filter);
		void RemoveAt(int Index);
		void RemoveAt(int BeginIndex, int EndIndex);
		void CopyTo(TElement* Array) const;
		void Resize(int Size);
		void Resize(int Size, TElement Value);
		void Sort();
		int Size() const;
		void Clear();

	public:

		void ForEach(ListDelegate Delegate) const;
		void ForEach(ListDelegate Delegate, ListFilter Filter) const;

	public:

		decltype(auto) begin();
		decltype(auto) end();

	};

	template<typename TElement>
	inline LinkedList<TElement>::LinkedList() : m_List()
	{
	
	}

	template<typename TElement>
	inline LinkedList<TElement>::LinkedList(int Capacity) : m_List(Capacity)
	{
	
	}

	template<typename TElement>
	inline LinkedList<TElement>::LinkedList(int Capacity, TElement Value) : m_List(Capacity, Value)
	{
	
	}

	template<typename TElement>
	inline LinkedList<TElement>::LinkedList(ListInitializer Initializer) : m_List(Initializer)
	{
	
	}

	template<typename TElement>
	inline LinkedList<TElement>::LinkedList(LinkedList<TElement>& Other)
	{
		m_List = std::list<TElement>(Other.m_List.size());
		for (unsigned int i = 0; i < m_Vector.size(); i++)
		{
			m_List[i] = Other.m_List[i];
		}
	}

	template<typename TElement>
	inline LinkedList<TElement>::LinkedList(LinkedList<TElement>&& Other)
	{
		m_List = Other.m_List;
	}

	template<typename TElement>
	inline TElement& LinkedList<TElement>::operator[](int Index)
	{
		if (Index < 0 || static_cast<unsigned int>(Index) >= m_List.size())
		{
			DEBUG_ERROR("LinkedList Index Out Of Range");
		}

		auto Iter = m_List.begin();
		for (unsigned int i = 0; i < m_List.size(); i++)
		{
			if (i == Index)
			{
				return *Iter;
			}
			Iter++;
		}
	}

	template<typename TElement>
	inline void LinkedList<TElement>::Add(TElement Element)
	{
		m_List.push_back(Element);
	}

	template<typename TElement>
	inline void LinkedList<TElement>::Add(const LinkedList<TElement>& Collection)
	{
		m_List.insert(m_List.end(), Collection.m_List.begin(), Collection.m_List.end());
	}

	template<typename TElement>
	inline bool LinkedList<TElement>::Contains(TElement Element) const
	{
		auto Iter = std::find(m_List.begin(), m_List.end(), Element);
		return Iter != m_List.end();
	}

	template<typename TElement>
	inline int LinkedList<TElement>::IndexOf(TElement Element) const
	{
		auto Iter = m_List.begin();
		for (unsigned int i = 0; i < m_List.size(); i++)
		{
			if (*Iter == Element)
			{
				return static_cast<int>(i);
			}
			Iter++;
		}
		return -1;
	}

	template<typename TElement>
	inline int LinkedList<TElement>::LastIndexOf(TElement Element) const
	{
		auto Iter = m_List.begin();
		for (unsigned int i = i < m_List.size() - 1; i >= 0; i--)
		{
			if (*Iter == Element)
			{
				return static_cast<int>(i);
			}
			Iter++;
		}
		return -1;
	}

	template<typename TElement>
	inline void LinkedList<TElement>::Insert(int Index, TElement Element)
	{
		if (Index < 0 || static_cast<unsigned int>(Index) >= m_List.size())
		{
			DEBUG_ERROR("LinkedList Index Out Of Range When Insert");
		}

		m_List.insert(m_List.begin() + Index, Element);
	}

	template<typename TElement>
	inline void LinkedList<TElement>::InsertRange(int Index, const LinkedList<TElement>& Collection)
	{
		if (Index < 0 || static_cast<unsigned int>(Index) >= m_List.size())
		{
			DEBUG_ERROR("LinkedList Index Out Of Range When InsertRange");
		}

		m_List.insert(m_List.begin() + Index, Collection.m_List.begin(), Collection.m_List.end());
	}

	template<typename TElement>
	inline void LinkedList<TElement>::Reverse()
	{
		std::reverse(m_List.begin(), m_List.end());
	}

	template<typename TElement>
	inline void LinkedList<TElement>::Reverse(int BeginIndex, int EndIndex)
	{
		if (BeginIndex < 0 || static_cast<unsigned int>(BeginIndex) >= m_List.size() ||
			EndIndex < 0 || static_cast<unsigned int>(EndIndex) >= m_List.size())
		{
			DEBUG_ERROR("LinkedList Index Out Of Range When Reverse");
		}

		std::reverse(m_List.begin() + BeginIndex, m_List.begin() + EndIndex);
	}

	template<typename TElement>
	inline LinkedList<TElement> LinkedList<TElement>::Find(ListFilter Filter) const
	{
		LinkedList<TElement> Result;
		for (auto Item : m_List)
		{
			if (Filter(Item))
			{
				Result.Add(Item);
			}
		}
		return Result;
	}

	template<typename TElement>
	inline int LinkedList<TElement>::Remove(TElement Element)
	{
		int RemoveCount = 0;
		auto Iter = m_List.begin();
		while (Iter != m_List.end())
		{
			if (*Iter == Element)
			{
				Iter = m_List.erase(Iter);
				RemoveCount++;
			}
			else
			{
				Iter++;
			}
		}
		return RemoveCount;
	}

	template<typename TElement>
	inline int LinkedList<TElement>::Remove(ListFilter Filter)
	{
		int RemoveCount = 0;
		auto Iter = m_List.begin();
		while (Iter != m_List.end())
		{
			if (Filter(*Iter))
			{
				Iter = m_List.erase(Iter);
				RemoveCount++;
			}
			else
			{
				Iter++;
			}
		}
		return RemoveCount;
	}

	template<typename TElement>
	inline void LinkedList<TElement>::RemoveAt(int Index)
	{
		if (Index < 0 || static_cast<unsigned int>(Index) >= m_List.size())
		{
			DEBUG_ERROR("LinkedList Index Out Of Range When RemoveAt");
		}

		m_List.erase(m_List.begin() + Index);
	}

	template<typename TElement>
	inline void LinkedList<TElement>::RemoveAt(int BeginIndex, int EndIndex)
	{
		if (BeginIndex < 0 || static_cast<unsigned int>(BeginIndex) >= m_List.size() ||
			EndIndex < 0 || static_cast<unsigned int>(EndIndex) >= m_List.size())
		{
			DEBUG_ERROR("LinkedList Index Out Of Range When RemoveAt");
		}

		m_List.erase(m_List.begin() + BeginIndex, m_List.begin() + EndIndex);
	}

	template<typename TElement>
	inline void LinkedList<TElement>::CopyTo(TElement* Array) const
	{
		auto Iter = m_List.begin();
		for (unsigned int i = 0; i < m_List.size(); i++)
		{
			Array[i] = *Iter;
			Iter++;
		}
	}

	template<typename TElement>
	inline void LinkedList<TElement>::Resize(int Size)
	{
		m_List.resize(Size);
	}

	template<typename TElement>
	inline void LinkedList<TElement>::Resize(int Size, TElement Value)
	{
		m_List.resize(Size, Value);
	}

	template<typename TElement>
	inline void LinkedList<TElement>::Sort()
	{
		m_List.sort();
	}

	template<typename TElement>
	inline int LinkedList<TElement>::Size() const
	{
		return m_List.size();
	}

	template<typename TElement>
	inline void LinkedList<TElement>::Clear()
	{
		m_List.clear();
	}

	template<typename TElement>
	inline void LinkedList<TElement>::ForEach(ListDelegate Delegate) const
	{
		for (auto Item : m_List)
		{
			Delegate(Item);
		}
	}

	template<typename TElement>
	inline void LinkedList<TElement>::ForEach(ListDelegate Delegate, ListFilter Filter) const
	{
		for (auto Item : m_List)
		{
			if (Filter(Item))
			{
				Delegate(Item);
			}
		}
	}

	template<typename TElement>
	inline decltype(auto) LinkedList<TElement>::begin()
	{
		m_List.begin();
	}

	template<typename TElement>
	inline decltype(auto) LinkedList<TElement>::end()
	{
		m_List.end();
	}
}
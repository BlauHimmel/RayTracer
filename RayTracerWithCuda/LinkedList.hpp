#pragma once

#ifndef __LINKEDLIST__
#define __LINKEDLIST__

#include "ContainerDependency.h"
#include "ContainerMacro.h"

namespace EasyContainer
{

	template<typename TElement>
	class LinkedList
	{

	public:

		using ListInitializer = std::initializer_list<TElement>;
		using ListDelegate = std::function<void(TElement&)>;
		using ListFilter = std::function<bool(TElement&)>;

	private:

		std::list<TElement> m_List;

	public:

		LinkedList();
		LinkedList(int32 Capacity);
		LinkedList(int32 Capacity, TElement Value);
		LinkedList(ListInitializer Initializer);

	public:

		TElement& operator [] (int32 Index);
		const TElement& operator [] (int32 Index) const;
		void Add(TElement Element);
		void Add(const LinkedList<TElement>& Collection);
		bool Contains(TElement Element) const;
		int32 IndexOf(TElement Element) const;
		int32 LastIndexOf(TElement Element) const;
		void Insert(int32 Index, TElement Element);
		void InsertRange(int32 Index, const LinkedList<TElement>& Collection);
		void Reverse();
		void Reverse(int32 BeginIndex, int32 EndIndex);
		std::unique_ptr<LinkedList<TElement>> Find(ListFilter Filter) const;
		int32 Remove(TElement Element);
		int32 Remove(ListFilter Filter);
		void RemoveAt(int32 Index);
		void RemoveAt(int32 BeginIndex, int32 EndIndex);
		void CopyTo(TElement* Array) const;
		void Resize(int32 Size);
		void Resize(int32 Size, TElement Value);
		void Sort();
		int32 Size() const;
		void Clear();

	public:

		void ForEach(ListDelegate Delegate) const;
		void ForEach(ListDelegate Delegate, ListFilter Filter) const;

	public:

		decltype(auto) begin() const;
		decltype(auto) end() const;

	};

	template<typename TElement>
	INLINE LinkedList<TElement>::LinkedList() : m_List()
	{
	
	}

	template<typename TElement>
	INLINE LinkedList<TElement>::LinkedList(int32 Capacity) : m_List(Capacity)
	{
	
	}

	template<typename TElement>
	INLINE LinkedList<TElement>::LinkedList(int32 Capacity, TElement Value) : m_List(Capacity, Value)
	{
	
	}

	template<typename TElement>
	INLINE LinkedList<TElement>::LinkedList(ListInitializer Initializer) : m_List(Initializer)
	{
	
	}

	template<typename TElement>
	INLINE TElement& LinkedList<TElement>::operator [] (int32 Index)
	{
		if (Index < 0 || static_cast<uint32>(Index) >= m_List.size())
		{
			DEBUG_ERROR("LinkedList Index Out Of Range");
		}

		auto Iter = m_List.begin();
		for (uint32 i = 0; i < m_List.size(); i++)
		{
			if (i == Index)
			{
				return *Iter;
			}
			Iter++;
		}
	}

	template<typename TElement>
	INLINE const TElement& LinkedList<TElement>::operator [] (int32 Index) const
	{
		if (Index < 0 || static_cast<uint32>(Index) >= m_List.size())
		{
			DEBUG_ERROR("LinkedList Index Out Of Range");
		}

		auto Iter = m_List.begin();
		for (uint32 i = 0; i < m_List.size(); i++)
		{
			if (i == Index)
			{
				return *Iter;
			}
			Iter++;
		}
	}

	template<typename TElement>
	INLINE void LinkedList<TElement>::Add(TElement Element)
	{
		m_List.push_back(Element);
	}

	template<typename TElement>
	INLINE void LinkedList<TElement>::Add(const LinkedList<TElement>& Collection)
	{
		m_List.insert(m_List.end(), Collection.m_List.begin(), Collection.m_List.end());
	}

	template<typename TElement>
	INLINE bool LinkedList<TElement>::Contains(TElement Element) const
	{
		auto Iter = std::find(m_List.begin(), m_List.end(), Element);
		return Iter != m_List.end();
	}

	template<typename TElement>
	INLINE int32 LinkedList<TElement>::IndexOf(TElement Element) const
	{
		auto Iter = m_List.begin();
		for (uint32 i = 0; i < m_List.size(); i++)
		{
			if (*Iter == Element)
			{
				return static_cast<int32>(i);
			}
			Iter++;
		}
		return -1;
	}

	template<typename TElement>
	INLINE int32 LinkedList<TElement>::LastIndexOf(TElement Element) const
	{
		auto Iter = m_List.end();
		Iter--;
		for (auto i = m_List.size() - 1; i >= 0; i--)
		{
			if (*Iter == Element)
			{
				return static_cast<int32>(i);
			}
			Iter--;
		}
		return -1;
	}

	template<typename TElement>
	INLINE void LinkedList<TElement>::Insert(int32 Index, TElement Element)
	{
		if (Index < 0 || static_cast<uint32>(Index) >= m_List.size())
		{
			DEBUG_ERROR("LinkedList Index Out Of Range When Insert");
		}

		auto BeginIter = m_List.begin();
		for (auto i = 0; i < Index; i++)
		{
			BeginIter ++;
		}

		m_List.insert(BeginIter, Element);
	}

	template<typename TElement>
	INLINE void LinkedList<TElement>::InsertRange(int32 Index, const LinkedList<TElement>& Collection)
	{
		if (Index < 0 || static_cast<uint32>(Index) >= m_List.size())
		{
			DEBUG_ERROR("LinkedList Index Out Of Range When InsertRange");
		}

		auto BeginIter = m_List.begin();
		for (auto i = 0; i < Index; i++)
		{
			BeginIter++;
		}

		m_List.insert(BeginIter, Collection.m_List.begin(), Collection.m_List.end());
	}

	template<typename TElement>
	INLINE void LinkedList<TElement>::Reverse()
	{
		std::reverse(m_List.begin(), m_List.end());
	}

	template<typename TElement>
	INLINE void LinkedList<TElement>::Reverse(int32 BeginIndex, int32 EndIndex)
	{
		if (BeginIndex < 0 || static_cast<uint32>(BeginIndex) >= m_List.size() ||
			EndIndex < 0 || static_cast<uint32>(EndIndex) >= m_List.size())
		{
			DEBUG_ERROR("LinkedList Index Out Of Range When Reverse");
		}

		auto BeginIter = m_List.begin();
		auto EndIter = m_List.begin();
		for (auto i = 0; i < BeginIndex; i++)
		{
			BeginIter++;
		}
		for (auto i = 0; i < EndIndex; i++)
		{
			EndIter++;
		}

		std::reverse(BeginIter, EndIter);
	}

	template<typename TElement>
	INLINE std::unique_ptr<LinkedList<TElement>> LinkedList<TElement>::Find(ListFilter Filter) const
	{
		std::unique_ptr<LinkedList<TElement>> PtrResult(new LinkedList<TElement>());
		for (auto Item : m_List)
		{
			if (Filter(Item))
			{
				PtrResult->Add(Item);
			}
		}
		return PtrResult;
	}

	template<typename TElement>
	INLINE int32 LinkedList<TElement>::Remove(TElement Element)
	{
		int32 RemoveCount = 0;
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
	INLINE int32 LinkedList<TElement>::Remove(ListFilter Filter)
	{
		int32 RemoveCount = 0;
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
	INLINE void LinkedList<TElement>::RemoveAt(int32 Index)
	{
		if (Index < 0 || static_cast<uint32>(Index) >= m_List.size())
		{
			DEBUG_ERROR("LinkedList Index Out Of Range When RemoveAt");
		}

		auto BeginIter = m_List.begin();
		for (auto i = 0; i < Index; i++)
		{
			BeginIter++;
		}

		m_List.erase(BeginIter);
	}

	template<typename TElement>
	INLINE void LinkedList<TElement>::RemoveAt(int32 BeginIndex, int32 EndIndex)
	{
		if (BeginIndex < 0 || static_cast<uint32>(BeginIndex) >= m_List.size() ||
			EndIndex < 0 || static_cast<uint32>(EndIndex) >= m_List.size())
		{
			DEBUG_ERROR("LinkedList Index Out Of Range When RemoveAt");
		}

		auto BeginIter = m_List.begin();
		auto EndIter = m_List.begin();
		for (auto i = 0; i < BeginIndex; i++)
		{
			BeginIter++;
		}
		for (auto i = 0; i < EndIndex; i++)
		{
			EndIter++;
		}

		m_List.erase(BeginIter, EndIter);
	}

	template<typename TElement>
	INLINE void LinkedList<TElement>::CopyTo(TElement* Array) const
	{
		auto Iter = m_List.begin();
		for (uint32 i = 0; i < m_List.size(); i++)
		{
			Array[i] = *Iter;
			Iter++;
		}
	}

	template<typename TElement>
	INLINE void LinkedList<TElement>::Resize(int32 Size)
	{
		m_List.resize(Size);
	}

	template<typename TElement>
	INLINE void LinkedList<TElement>::Resize(int32 Size, TElement Value)
	{
		m_List.resize(Size, Value);
	}

	template<typename TElement>
	INLINE void LinkedList<TElement>::Sort()
	{
		m_List.sort();
	}

	template<typename TElement>
	INLINE int32 LinkedList<TElement>::Size() const
	{
		return m_List.size();
	}

	template<typename TElement>
	INLINE void LinkedList<TElement>::Clear()
	{
		m_List.clear();
	}

	template<typename TElement>
	INLINE void LinkedList<TElement>::ForEach(ListDelegate Delegate) const
	{
		for (auto Item : m_List)
		{
			Delegate(Item);
		}
	}

	template<typename TElement>
	INLINE void LinkedList<TElement>::ForEach(ListDelegate Delegate, ListFilter Filter) const
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
	INLINE decltype(auto) LinkedList<TElement>::begin() const
	{
		m_List.begin();
	}

	template<typename TElement>
	INLINE decltype(auto) LinkedList<TElement>::end() const
	{
		m_List.end();
	}
}

#endif
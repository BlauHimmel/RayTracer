#pragma once

#ifndef __HASHSET__
#define __HASHSET__

#include "ContainerDependency.h"
#include "ContainerMacro.h"

namespace EasyContainer
{

	template<typename TElement>
	class HashSet
	{

	public:

		using SetInitializer = std::initializer_list<TElement>;
		using SetDelegate = std::function<void(TElement&)>;
		using SetFilter = std::function<bool(TElement&)>;

	private:

		std::unordered_set<TElement> m_Set;

	public:

		HashSet();
		HashSet(SetInitializer Initializer);

	public:

		bool Add(TElement Element);
		void Clear();
		bool Contains(TElement Element) const;
		bool Remove(TElement Element);
		int32 Remove(SetFilter Filter);
		void CopyTo(TElement* Array) const;
		std::unique_ptr<HashSet<TElement>> Intersect(const HashSet<TElement>& OtherSet) const;
		std::unique_ptr<HashSet<TElement>> Union(const HashSet<TElement>& OtherSet) const;
		std::unique_ptr<HashSet<TElement>> Difference(const HashSet<TElement>& OtherSet) const;
		std::unique_ptr<HashSet<TElement>> SymmetricDifference(const HashSet<TElement>& OtherSet) const;

	public:

		virtual void ForEach(SetDelegate Delegate) const;
		virtual void ForEach(SetDelegate Delegate, SetFilter Filter) const;

	public:

		decltype(auto) begin() const;
		decltype(auto) end() const;

	};

	template<typename TElement>
	INLINE HashSet<TElement>::HashSet() : m_Set()
	{
	
	}

	template<typename TElement>
	INLINE HashSet<TElement>::HashSet(SetInitializer Initializer) : m_Set(Initializer)
	{
	
	}

	template<typename TElement>
	INLINE bool HashSet<TElement>::Add(TElement Element)
	{
		return m_Set.insert(Element);
	}

	template<typename TElement>
	INLINE void HashSet<TElement>::Clear()
	{
		m_Set.clear();
	}

	template<typename TElement>
	INLINE bool HashSet<TElement>::Contains(TElement Element) const
	{
		return m_Set.count(Element) > 0;
	}

	template<typename TElement>
	INLINE bool HashSet<TElement>::Remove(TElement Element)
	{
		return m_Set.erase(Element) > 0;
	}

	template<typename TElement>
	INLINE int32 HashSet<TElement>::Remove(SetFilter Filter)
	{
		int32 RemoveCount = 0;
		auto Iter = m_Set.begin();
		while (Iter != m_Set.end())
		{
			if (Filter(*Iter))
			{
				Iter = m_Set.erase(Iter);
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
	INLINE void HashSet<TElement>::CopyTo(TElement* Array) const
	{
		for (uint32 i = 0; i < m_Set.size(); i++)
		{
			Array[i] = m_Set[i];
		}
	}

	template<typename TElement>
	INLINE std::unique_ptr<HashSet<TElement>> HashSet<TElement>::Intersect(const HashSet<TElement>& OtherSet) const
	{
		std::unique_ptr<HashSet<TElement>> PtrResult(new HashSet<TElement>());
		std::set_intersection(m_Set.begin(), m_Set.end(), OtherSet.m_Set.begin(), OtherSet.m_Set.end(), 
			std::insert_iterator<std::unordered_set<int32>>(PtrResult->m_Set, PtrResult->m_Set.begin()));
		return PtrResult;
	}

	template<typename TElement>
	INLINE std::unique_ptr<HashSet<TElement>> HashSet<TElement>::Union(const HashSet<TElement>& OtherSet) const
	{
		std::unique_ptr<HashSet<TElement>> PtrResult(new HashSet<TElement>());
		std::set_union(m_Set.begin(), m_Set.end(), OtherSet.m_Set.begin(), OtherSet.m_Set.end(), 
			std::insert_iterator<std::unordered_set<int32>>(PtrResult->m_Set, PtrResult->m_Set.begin()));
		return PtrResult;
	}

	template<typename TElement>
	INLINE std::unique_ptr<HashSet<TElement>> HashSet<TElement>::Difference(const HashSet<TElement>& OtherSet) const
	{
		std::unique_ptr<HashSet<TElement>> PtrResult(new HashSet<TElement>());
		std::set_difference(m_Set.begin(), m_Set.end(), OtherSet.m_Set.begin(), OtherSet.m_Set.end(), 
			std::insert_iterator<std::unordered_set<int32>>(PtrResult->m_Set, PtrResult->m_Set.begin()));
		return PtrResult;
	}

	template<typename TElement>
	INLINE std::unique_ptr<HashSet<TElement>> HashSet<TElement>::SymmetricDifference(const HashSet<TElement>& OtherSet) const
	{
		std::unique_ptr<HashSet<TElement>> PtrResult(new HashSet<TElement>());
		std::set_symmetric_difference(m_Set.begin(), m_Set.end(), OtherSet.m_Set.begin(), OtherSet.m_Set.end(), 
			std::insert_iterator<std::unordered_set<int32>>(PtrResult->m_Set, PtrResult->m_Set.begin()));
		return PtrResult;
	}

	template<typename TElement>
	INLINE void HashSet<TElement>::ForEach(SetDelegate Delegate) const
	{
		for (auto Item : m_Set)
		{
			Delegate(Item);
		}
	}

	template<typename TElement>
	INLINE void HashSet<TElement>::ForEach(SetDelegate Delegate, SetFilter Filter) const
	{
		for (auto Item : m_Set)
		{
			if (Filter(Item))
			{
				Delegate(Item);
			}
		}
	}

	template<typename TElement>
	INLINE decltype(auto) HashSet<TElement>::begin() const
	{
		m_Set.begin();
	}

	template<typename TElement>
	INLINE decltype(auto) HashSet<TElement>::end() const
	{
		m_Set.end();
	}
}

#endif
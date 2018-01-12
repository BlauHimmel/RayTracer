#pragma once

#ifndef __TREESET__
#define __TREESET__

#include "Container\Dependency\ContainerDependency.h"
#include "Container\Dependency\ContainerMacro.h"

namespace EasyContainer
{

	template<typename TElement>
	class TreeSet
	{

	public:

		using SetInitializer = std::initializer_list<TElement>;
		using SetDelegate = std::function<void(TElement&)>;
		using SetFilter = std::function<bool(TElement&)>;

	private:

		std::set<TElement> m_Set;

	public:

		TreeSet();
		TreeSet(SetInitializer Initializer);

	public:

		bool Add(TElement Element);
		void Clear();
		bool Contains(TElement Element) const;
		bool Remove(TElement Element);
		int32 Remove(SetFilter Filter);
		void CopyTo(TElement* Array) const;
		std::unique_ptr<TreeSet<TElement>> Intersect(const TreeSet<TElement>& OtherSet) const;
		std::unique_ptr<TreeSet<TElement>> Union(const TreeSet<TElement>& OtherSet) const;
		std::unique_ptr<TreeSet<TElement>> Difference(const TreeSet<TElement>& OtherSet) const;
		std::unique_ptr<TreeSet<TElement>> SymmetricDifference(const TreeSet<TElement>& OtherSet) const;

	public:

		void ForEach(SetDelegate Delegate) const;
		void ForEach(SetDelegate Delegate, SetFilter Filter) const;

	public:

		decltype(auto) begin() const;
		decltype(auto) end() const;

	};

	template<typename TElement>
	INLINE TreeSet<TElement>::TreeSet() : m_Set()
	{
	
	}

	template<typename TElement>
	INLINE TreeSet<TElement>::TreeSet(SetInitializer Initializer) : m_Set(Initializer)
	{
	
	}

	template<typename TElement>
	INLINE bool TreeSet<TElement>::Add(TElement Element)
	{
		return m_Set.insert(Element);
	}

	template<typename TElement>
	INLINE void TreeSet<TElement>::Clear()
	{
		m_Set.clear();
	}

	template<typename TElement>
	INLINE bool TreeSet<TElement>::Contains(TElement Element) const
	{
		return m_Set.count(Element) > 0;
	}

	template<typename TElement>
	INLINE bool TreeSet<TElement>::Remove(TElement Element)
	{
		return m_Set.erase(Element) > 0;
	}

	template<typename TElement>
	INLINE int32 TreeSet<TElement>::Remove(SetFilter Filter)
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
	INLINE void TreeSet<TElement>::CopyTo(TElement* Array) const
	{
		for (auto i = 0; i < m_Set.size(); i++)
		{
			Array[i] = m_Set[i];
		}
	}

	template<typename TElement>
	INLINE std::unique_ptr<TreeSet<TElement>> TreeSet<TElement>::Intersect(const TreeSet<TElement>& OtherSet) const
	{
		std::unique_ptr<TreeSet<TElement>> PtrResult(new TreeSet<TElement>());
		std::set_intersection(m_Set.begin(), m_Set.end(), OtherSet.m_Set.begin(), OtherSet.m_Set.end(), 
			std::insert_iterator<std::unordered_set<int32>>(PtrResult->m_Set, PtrResult->m_Set.begin()));
		return PtrResult;
	}

	template<typename TElement>
	INLINE std::unique_ptr<TreeSet<TElement>> TreeSet<TElement>::Union(const TreeSet<TElement>& OtherSet) const
	{
		std::unique_ptr<TreeSet<TElement>> PtrResult(new TreeSet<TElement>());
		std::set_union(m_Set.begin(), m_Set.end(), OtherSet.m_Set.begin(), OtherSet.m_Set.end(), 
			std::insert_iterator<std::unordered_set<int32>>(PtrResult->m_Set, PtrResult->m_Set.begin()));
		return PtrResult;
	}

	template<typename TElement>
	INLINE std::unique_ptr<TreeSet<TElement>> TreeSet<TElement>::Difference(const TreeSet<TElement>& OtherSet) const
	{
		std::unique_ptr<TreeSet<TElement>> PtrResult(new TreeSet<TElement>());
		std::set_difference(m_Set.begin(), m_Set.end(), OtherSet.m_Set.begin(), OtherSet.m_Set.end(), 
			std::insert_iterator<std::unordered_set<int32>>(PtrResult->m_Set, PtrResult->m_Set.begin()));
		return PtrResult;
	}

	template<typename TElement>
	INLINE std::unique_ptr<TreeSet<TElement>> TreeSet<TElement>::SymmetricDifference(const TreeSet<TElement>& OtherSet) const
	{
		std::unique_ptr<TreeSet<TElement>> PtrResult(new TreeSet<TElement>());
		std::set_symmetric_difference(m_Set.begin(), m_Set.end(), OtherSet.m_Set.begin(), OtherSet.m_Set.end(), 
			std::insert_iterator<std::unordered_set<int32>>(PtrResult->m_Set, PtrResult->m_Set.begin()));
		return PtrResult;
	}

	template<typename TElement>
	INLINE void TreeSet<TElement>::ForEach(SetDelegate Delegate) const
	{
		for (auto Item : m_Set)
		{
			Delegate(Item);
		}
	}

	template<typename TElement>
	INLINE void TreeSet<TElement>::ForEach(SetDelegate Delegate, SetFilter Filter) const
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
	INLINE decltype(auto) TreeSet<TElement>::begin() const
	{
		m_Set.begin();
	}

	template<typename TElement>
	INLINE decltype(auto) TreeSet<TElement>::end() const
	{
		m_Set.end();
	}
}

#endif
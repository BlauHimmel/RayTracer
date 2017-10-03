#pragma once

#include "ContainerDependency.h"
#include "ContainerMacro.h"

namespace EasyContainer
{

	template<typename TElement>
	class TreeSet
	{

	public:

		using SetInitializer = std::initializer_list<TElement>;
		using SetDelegate = std::function<void(TElement)>;
		using SetFilter = std::function<bool(TElement)>;

	private:

		std::set<TElement> m_Set;

	public:

		TreeSet();
		TreeSet(SetInitializer Initializer);
		TreeSet(TreeSet<TElement>& Other);
		TreeSet(TreeSet<TElement>&& Other);

	public:

		bool Add(TElement Element);
		void Clear();
		bool Contains(TElement Element) const;
		bool Remove(TElement Element);
		int32 Remove(SetFilter Filter);
		void CopyTo(TElement* Array) const;
		TreeSet<TElement> Intersect(const TreeSet<TElement>& OtherSet) const;
		TreeSet<TElement> Union(const TreeSet<TElement>& OtherSet) const;
		TreeSet<TElement> Difference(const TreeSet<TElement>& OtherSet) const;
		TreeSet<TElement> SymmetricDifference(const TreeSet<TElement>& OtherSet) const;

	public:

		void ForEach(SetDelegate Delegate) const;
		void ForEach(SetDelegate Delegate, SetFilter Filter) const;

	public:

		decltype(auto) begin();
		decltype(auto) end();

	};

	template<typename TElement>
	inline TreeSet<TElement>::TreeSet() : m_Set()
	{
	
	}

	template<typename TElement>
	inline TreeSet<TElement>::TreeSet(SetInitializer Initializer) : m_Set(Initializer)
	{
	
	}

	template<typename TElement>
	inline TreeSet<TElement>::TreeSet(TreeSet<TElement>& Other)
	{
		m_Set = std::set<TElement>();
		for (auto Iter = m_Set.begin(); Iter != m_Set.end(); Iter++)
		{
			m_Set.insert(*Iter);
		}
	}

	template<typename TElement>
	inline TreeSet<TElement>::TreeSet(TreeSet<TElement>&& Other)
	{
		m_Set = Other.m_Set;
	}

	template<typename TElement>
	inline bool TreeSet<TElement>::Add(TElement Element)
	{
		return m_Set.insert(Element);
	}

	template<typename TElement>
	inline void TreeSet<TElement>::Clear()
	{
		m_Set.clear();
	}

	template<typename TElement>
	inline bool TreeSet<TElement>::Contains(TElement Element) const
	{
		return m_Set.count(Element) > 0;
	}

	template<typename TElement>
	inline bool TreeSet<TElement>::Remove(TElement Element)
	{
		return m_Set.erase(Element) > 0;
	}

	template<typename TElement>
	inline int32 TreeSet<TElement>::Remove(SetFilter Filter)
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
	inline void TreeSet<TElement>::CopyTo(TElement* Array) const
	{
		for (uint32 i = 0; i < m_Set.size(); i++)
		{
			Array[i] = m_Set[i];
		}
	}

	template<typename TElement>
	inline TreeSet<TElement> TreeSet<TElement>::Intersect(const TreeSet<TElement>& OtherSet) const
	{
		TreeSet<TElement> Result;
		std::set_intersection(m_Set.begin(), m_Set.end(), OtherSet.m_Set.begin(), OtherSet.m_Set.end(), 
			std::insert_iterator<std::unordered_set<int32>>(Result.m_Set, Result.m_Set.begin()));
		return Result;
	}

	template<typename TElement>
	inline TreeSet<TElement> TreeSet<TElement>::Union(const TreeSet<TElement>& OtherSet) const
	{
		TreeSet<TElement> Result;
		std::set_union(m_Set.begin(), m_Set.end(), OtherSet.m_Set.begin(), OtherSet.m_Set.end(), 
			std::insert_iterator<std::unordered_set<int32>>(Result.m_Set, Result.m_Set.begin()));
		return Result;
	}

	template<typename TElement>
	inline TreeSet<TElement> TreeSet<TElement>::Difference(const TreeSet<TElement>& OtherSet) const
	{
		TreeSet<TElement> Result;
		std::set_difference(m_Set.begin(), m_Set.end(), OtherSet.m_Set.begin(), OtherSet.m_Set.end(), 
			std::insert_iterator<std::unordered_set<int32>>(Result.m_Set, Result.m_Set.begin()));
		return Result;
	}

	template<typename TElement>
	inline TreeSet<TElement> TreeSet<TElement>::SymmetricDifference(const TreeSet<TElement>& OtherSet) const
	{
		TreeSet<TElement> Result;
		std::set_symmetric_difference(m_Set.begin(), m_Set.end(), OtherSet.m_Set.begin(), OtherSet.m_Set.end(), 
			std::insert_iterator<std::unordered_set<int32>>(Result.m_Set, Result.m_Set.begin()));
		return Result;
	}

	template<typename TElement>
	inline void TreeSet<TElement>::ForEach(SetDelegate Delegate) const
	{
		for (auto Item : m_Set)
		{
			Delegate(Item);
		}
	}

	template<typename TElement>
	inline void TreeSet<TElement>::ForEach(SetDelegate Delegate, SetFilter Filter) const
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
	inline decltype(auto) TreeSet<TElement>::begin()
	{
		m_Set.begin();
	}

	template<typename TElement>
	inline decltype(auto) TreeSet<TElement>::end()
	{
		m_Set.end();
	}
}
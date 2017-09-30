#pragma once

#include "TemplateDependency.h"
#include "TemplateMacro.h"
#include "GlobalDependency.h"
#include "GlobalMacro.h"

namespace EasyTemplate
{

	template<typename TElement>
	class HashSet
	{

		template<typename TElement> friend class HashSet;

	public:

		using SetInitializer = std::initializer_list<TElement>;
		using SetDelegate = std::function<void(TElement)>;
		using SetFilter = std::function<bool(TElement)>;

	private:

		std::unordered_set<TElement> m_Set;

	public:

		HashSet();
		HashSet(SetInitializer Initializer);
		HashSet(HashSet<TElement>& Other);
		HashSet(HashSet<TElement>&& Other);
		
	public:

		bool Add(TElement Element);
		void Clear();
		bool Contains(TElement Element) const;
		bool Remove(TElement Element);
		int Remove(SetFilter Filter);
		void CopyTo(TElement* Array) const;
		HashSet<TElement> Intersect(const HashSet<TElement>& OtherSet) const;
		HashSet<TElement> Union(const HashSet<TElement>& OtherSet) const;
		HashSet<TElement> Difference(const HashSet<TElement>& OtherSet) const;
		HashSet<TElement> SymmetricDifference(const HashSet<TElement>& OtherSet) const;

	public:

		virtual void ForEach(SetDelegate Delegate) const;
		virtual void ForEach(SetDelegate Delegate, SetFilter Filter) const;

	public:

		decltype(auto) begin();
		decltype(auto) end();
	};

	template<typename TElement>
	inline HashSet<TElement>::HashSet() : m_Set()
	{
	
	}

	template<typename TElement>
	inline HashSet<TElement>::HashSet(SetInitializer Initializer) : m_Set(Initializer)
	{
	
	}

	template<typename TElement>
	inline HashSet<TElement>::HashSet(HashSet<TElement>& Other)
	{
		m_Set = std::unordered_set<TElement>();
		for (auto Iter = m_Set.begin(); Iter != m_Set.end(); Iter++)
		{
			m_Set.insert(*Iter);
		}
	}

	template<typename TElement>
	inline HashSet<TElement>::HashSet(HashSet<TElement>&& Other)
	{
		m_Set = Other.m_Set;
	}

	template<typename TElement>
	inline bool HashSet<TElement>::Add(TElement Element)
	{
		return m_Set.insert(Element);
	}

	template<typename TElement>
	inline void HashSet<TElement>::Clear()
	{
		m_Set.clear();
	}

	template<typename TElement>
	inline bool HashSet<TElement>::Contains(TElement Element) const
	{
		return m_Set.count(Element) > 0;
	}

	template<typename TElement>
	inline bool HashSet<TElement>::Remove(TElement Element)
	{
		return m_Set.erase(Element) > 0;
	}

	template<typename TElement>
	inline int HashSet<TElement>::Remove(SetFilter Filter)
	{
		int RemoveCount = 0;
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
	inline void HashSet<TElement>::CopyTo(TElement * Array) const
	{
		for (unsigned int i = 0; i < m_Set.size(); i++)
		{
			Array[i] = m_Set[i];
		}
	}

	template<typename TElement>
	inline HashSet<TElement> HashSet<TElement>::Intersect(const HashSet<TElement>& OtherSet) const
	{
		HashSet<TElement> Result;
		std::set_intersection(m_Set.begin(), m_Set.end(), OtherSet.m_Set.begin(), OtherSet.m_Set.end(), 
			std::insert_iterator<std::unordered_set<int>>(Result.m_Set, Result.m_Set.begin()));
		return Result;
	}

	template<typename TElement>
	inline HashSet<TElement> HashSet<TElement>::Union(const HashSet<TElement>& OtherSet) const
	{
		HashSet<TElement> Result;
		std::set_union(m_Set.begin(), m_Set.end(), OtherSet.m_Set.begin(), OtherSet.m_Set.end(), 
			std::insert_iterator<std::unordered_set<int>>(Result.m_Set, Result.m_Set.begin()));
		return Result;
	}

	template<typename TElement>
	inline HashSet<TElement> HashSet<TElement>::Difference(const HashSet<TElement>& OtherSet) const
	{
		HashSet<TElement> Result;
		std::set_difference(m_Set.begin(), m_Set.end(), OtherSet.m_Set.begin(), OtherSet.m_Set.end(), 
			std::insert_iterator<std::unordered_set<int>>(Result.m_Set, Result.m_Set.begin()));
		return Result;
	}

	template<typename TElement>
	inline HashSet<TElement> HashSet<TElement>::SymmetricDifference(const HashSet<TElement>& OtherSet) const
	{
		HashSet<TElement> Result;
		std::set_symmetric_difference(m_Set.begin(), m_Set.end(), OtherSet.m_Set.begin(), OtherSet.m_Set.end(), 
			std::insert_iterator<std::unordered_set<int>>(Result.m_Set, Result.m_Set.begin()));
		return Result;
	}

	template<typename TElement>
	inline void HashSet<TElement>::ForEach(SetDelegate Delegate) const
	{
		for (auto Item : m_Set)
		{
			Delegate(Item);
		}
	}

	template<typename TElement>
	inline void HashSet<TElement>::ForEach(SetDelegate Delegate, SetFilter Filter) const
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
	inline decltype(auto) HashSet<TElement>::begin()
	{
		m_Set.begin();
	}

	template<typename TElement>
	inline decltype(auto) HashSet<TElement>::end()
	{
		m_Set.end();
	}
}
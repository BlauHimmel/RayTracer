#pragma once

#include "TemplateDependency.h"
#include "TemplateMacro.h"
#include "GlobalDependency.h"
#include "GlobalMacro.h"

namespace EasyTemplate
{

	template<typename TElement>
	class ArrayList
	{

		template<typename TElement> friend class ArrayList;

	public:

		using ListInitializer = std::initializer_list<TElement>;
		using ListDelegate = std::function<void(TElement)>;
		using ListFilter = std::function<bool(TElement)>;

	private:

		std::vector<TElement> m_Vector;

	public:

		ArrayList();
		ArrayList(int Capacity);
		ArrayList(int Capacity, TElement Value);
		ArrayList(ListInitializer Initializer);
		ArrayList(ArrayList<TElement>& Other);
		ArrayList(ArrayList<TElement>&& Other);

	public:

		TElement& operator[](int Index);
		void Add(TElement Element);
		void Add(const ArrayList<TElement>& Collection);
		bool Contains(TElement Element) const;
		int IndexOf(TElement Element) const;
		int LastIndexOf(TElement Element) const;
		void Insert(int Index, TElement Element);
		void InsertRange(int Index, ArrayList<TElement> Collection);
		void Reverse();
		void Reverse(int BeginIndex, int EndIndex);
		ArrayList<TElement> Find(ListFilter Filter) const;
		int Remove(TElement Element);
		int Remove(ListFilter Filter);
		void RemoveAt(int Index);
		void RemoveAt(int BeginIndex, int EndIndex);
		void CopyTo(TElement* Array) const;
		void Resize(int Size);
		void Resize(int Size, TElement Value);
		void Sort();
		int Size() const;
		int Capacity() const;
		void Clear();

	public:

		void ForEach(ListDelegate Delegate) const;
		void ForEach(ListDelegate Delegate, ListFilter Filter) const;

	public:

		decltype(auto) begin();
		decltype(auto) end();

	};

	template<typename TElement>
	inline ArrayList<TElement>::ArrayList() : m_Vector()
	{
	
	}

	template<typename TElement>
	inline ArrayList<TElement>::ArrayList(int Capacity) : m_Vector(Capacity)
	{
	
	}

	template<typename TElement>
	inline ArrayList<TElement>::ArrayList(int Capacity, TElement Value) : m_Vector(Capacity, Value)
	{
	
	}

	template<typename TElement>
	inline ArrayList<TElement>::ArrayList(ListInitializer Initializer) : m_Vector(Initializer)
	{
	
	}

	template<typename TElement>
	inline ArrayList<TElement>::ArrayList(ArrayList<TElement>& Other)
	{
		m_Vector = std::vector<TElement>(Other.m_Vector.size());
		for (unsigned int i = 0; i < m_Vector.size(); i++)
		{
			m_Vector[i] = Other.m_Vector[i];
		}
	}

	template<typename TElement>
	inline ArrayList<TElement>::ArrayList(ArrayList<TElement>&& Other)
	{
		m_Vector = Other.m_Vector;
	}

	template<typename TElement>
	inline TElement& ArrayList<TElement>::operator[](int Index)
	{
		if (Index < 0 || static_cast<unsigned int>(Index) >= m_Vector.size())
		{
			DEBUG_ERROR("ArrayList Index Out Of Range");
		}

		return m_Vector[Index];
	}

	template<typename TElement>
	inline void ArrayList<TElement>::Add(TElement Element)
	{
		m_Vector.push_back(Element);
	}

	template<typename TElement>
	inline void ArrayList<TElement>::Add(const ArrayList<TElement>& Collection)
	{
		m_Vector.insert(m_Vector.end(), Collection.m_Vector.begin(), Collection.m_Vector.end());
	}

	template<typename TElement>
	inline bool ArrayList<TElement>::Contains(TElement Element) const
	{
		auto Iter = std::find(m_Vector.begin(), m_Vector.end(), Element);
		return Iter != m_Vector.end();
	}

	template<typename TElement>
	inline int ArrayList<TElement>::IndexOf(TElement Element) const
	{
		for (unsigned int i = 0; i < m_Vector.size(); i++)
		{
			if (m_Vector[i] == Element)
			{
				return static_cast<int>(i);
			}
		}
		return -1;
	}

	template<typename TElement>
	inline int ArrayList<TElement>::LastIndexOf(TElement Element) const
	{
		for (unsigned int i = m_Vector.size() - 1; i >= 0; i--)
		{
			if (m_Vector[i] == Element)
			{
				return static_cast<int>(i);
			}
		}
		return -1;
	}

	template<typename TElement>
	inline void ArrayList<TElement>::Insert(int Index, TElement Element)
	{
		if (Index < 0 || static_cast<unsigned int>(Index) >= m_Vector.size())
		{
			DEBUG_ERROR("ArrayList Index Out Of Range When Insert");
		}

		m_Vector.insert(m_Vector.begin() + Index, Element);
	}

	template<typename TElement>
	inline void ArrayList<TElement>::InsertRange(int Index, ArrayList<TElement> Collection)
	{
		if (Index < 0 || static_cast<unsigned int>(Index) >= m_Vector.size())
		{
			DEBUG_ERROR("ArrayList Index Out Of Range When InsertRange");
		}

		m_Vector.insert(m_Vector.begin() + Index, Collection.m_Vector.begin(), Collection.m_Vector.end());
	}

	template<typename TElement>
	inline void ArrayList<TElement>::Reverse()
	{
		std::reverse(m_Vector.begin(), m_Vector.end());
	}

	template<typename TElement>
	inline void ArrayList<TElement>::Reverse(int BeginIndex, int EndIndex)
	{
		if (BeginIndex < 0 || static_cast<unsigned int>(BeginIndex) >= m_Vector.size() ||
			EndIndex < 0 || static_cast<unsigned int>(EndIndex) >= m_Vector.size())
		{
			DEBUG_ERROR("ArrayList Index Out Of Range When Reverse");
		}

		std::reverse(m_Vector.begin() + BeginIndex, m_Vector.begin() + EndIndex);
	}

	template<typename TElement>
	inline ArrayList<TElement> ArrayList<TElement>::Find(ListFilter Filter) const
	{
		ArrayList<TElement> Result;
		for (auto Item : m_Vector)
		{
			if (Filter(Item))
			{
				Result.Add(Item);
			}
		}
		return Result;
	}

	template<typename TElement>
	inline int ArrayList<TElement>::Remove(TElement Element)
	{
		int RemoveCount = 0;
		auto Iter = m_Vector.begin();
		while (Iter != m_Vector.end())
		{
			if (*Iter == Element)
			{
				Iter = m_Vector.erase(Iter);
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
	inline int ArrayList<TElement>::Remove(ListFilter Filter)
	{
		int RemoveCount = 0;
		auto Iter = m_Vector.begin();
		while (Iter != m_Vector.end())
		{
			if (Filter(*Iter))
			{
				Iter = m_Vector.erase(Iter);
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
	inline void ArrayList<TElement>::RemoveAt(int Index)
	{
		if (Index < 0 || static_cast<unsigned int>(Index) >= m_Vector.size())
		{
			DEBUG_ERROR("ArrayList Index Out Of Range When RemoveAt");
		}

		m_Vector.erase(m_Vector.begin() + Index);
	}

	template<typename TElement>
	inline void ArrayList<TElement>::RemoveAt(int BeginIndex, int EndIndex)
	{
		if (BeginIndex < 0 || static_cast<unsigned int>(BeginIndex) >= m_Vector.size() ||
			EndIndex < 0 || static_cast<unsigned int>(EndIndex) >= m_Vector.size())
		{
			DEBUG_ERROR("ArrayList Index Out Of Range When RemoveAt");
		}

		m_Vector.erase(m_Vector.begin() + BeginIndex, m_Vector.begin() + EndIndex);
	}

	template<typename TElement>
	inline void ArrayList<TElement>::CopyTo(TElement* Array) const
	{
		for (unsigned int i = 0; i < m_Vector.size(); i++)
		{
			Array[i] = m_Vector[i];
		}
	}

	template<typename TElement>
	inline void ArrayList<TElement>::Resize(int Size)
	{
		m_Vector.resize(Size);
	}

	template<typename TElement>
	inline void ArrayList<TElement>::Resize(int Size, TElement Value)
	{
		m_Vector.resize(Size, Value);
	}

	template<typename TElement>
	inline void ArrayList<TElement>::Sort()
	{
		std::sort(m_Vector.begin(), m_Vector.end());
	}

	template<typename TElement>
	inline int ArrayList<TElement>::Size() const
	{
		return m_Vector.size();
	}

	template<typename TElement>
	inline int ArrayList<TElement>::Capacity() const
	{
		return m_Vector.capacity();
	}

	template<typename TElement>
	inline void ArrayList<TElement>::Clear()
	{
		m_Vector.clear();
	}

	template<typename TElement>
	inline void ArrayList<TElement>::ForEach(ListDelegate Delegate) const
	{
		for (auto Item : m_Vector)
		{
			Delegate(Item);
		}
	}

	template<typename TElement>
	inline void ArrayList<TElement>::ForEach(ListDelegate Delegate, ListFilter Filter) const
	{
		for (auto Item : m_Vector)
		{
			if (Filter(Item))
			{
				Delegate(Item);
			}
		}
	}

	template<typename TElement>
	inline decltype(auto) ArrayList<TElement>::begin()
	{
		return m_Vector.begin();
	}

	template<typename TElement>
	inline decltype(auto) ArrayList<TElement>::end()
	{
		return m_Vector.end();
	}
}
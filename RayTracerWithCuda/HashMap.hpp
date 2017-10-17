#pragma once

#include "ContainerDependency.h"
#include "ContainerMacro.h"

namespace EasyContainer
{

	template<typename TKey, typename TValue>
	class HashMap
	{

	public:

		using Pair = std::pair<TKey, TValue>;
		using MapInitializer = std::initializer_list<Pair>;
		using MapDelegate = std::function<void(TKey&, TValue&)>;
		using MapFilter = std::function<bool(TKey&, TValue&)>;

	private:

		std::unordered_map<TKey, TValue> m_Map;

	public:

		HashMap();
		HashMap(MapInitializer Initializer);

	public:

		TValue& operator [] (TKey Key);
		bool Add(TKey Key, TValue Value);
		bool TryGetValue(TKey Key, TValue*& Out_ValuePtr);
		bool ContainsKey(TKey Key) const;
		bool Remove(TKey Key);
		int32 Size() const;
		void Clear();

	public:

		void ForEach(MapDelegate Delegate) const;
		void ForEach(MapDelegate Delegate, MapFilter Filter) const;

	public:

		decltype(auto) begin() const;
		decltype(auto) end() const;

	};

	template<typename TKey, typename TValue>
	INLINE HashMap<TKey, TValue>::HashMap() : m_Map()
	{
	
	}

	template<typename TKey, typename TValue>
	INLINE HashMap<TKey, TValue>::HashMap(MapInitializer Initializer) : m_Map(Initializer)
	{
	
	}

	template<typename TKey, typename TValue>
	INLINE TValue& HashMap<TKey, TValue>::operator [] (TKey Key)
	{
		return m_Map[Key];
	}

	template<typename TKey, typename TValue>
	INLINE bool HashMap<TKey, TValue>::Add(TKey Key, TValue Value)
	{
		return m_Map.insert(Pair(Key, Value)).second;
	}

	template<typename TKey, typename TValue>
	INLINE bool HashMap<TKey, TValue>::TryGetValue(TKey Key, TValue*& Out_ValuePtr)
	{
		auto iter = m_Map.find(Key);
		if (iter != m_Map.end())
		{
			OutValuePtr = &iter->second;
			return true;
		}
		else
		{
			OutValuePtr = nullptr;
			return false;
		}
	}

	template<typename TKey, typename TValue>
	INLINE bool HashMap<TKey, TValue>::ContainsKey(TKey Key) const
	{
		return m_Map.count(Key) > 0;
	}

	template<typename TKey, typename TValue>
	INLINE bool HashMap<TKey, TValue>::Remove(TKey Key)
	{
		return m_Map.erase(Key) == 1;
	}

	template<typename TKey, typename TValue>
	INLINE int32 HashMap<TKey, TValue>::Size() const
	{
		return m_Map.size();
	}

	template<typename TKey, typename TValue>
	INLINE void HashMap<TKey, TValue>::Clear()
	{
		m_Map.clear();
	}

	template<typename TKey, typename TValue>
	INLINE void HashMap<TKey, TValue>::ForEach(MapDelegate Delegate) const
	{
		for (auto Pair : m_Map)
		{
			Delegate(Pair.first, Pair.second);
		}
	}

	template<typename TKey, typename TValue>
	INLINE void HashMap<TKey, TValue>::ForEach(MapDelegate Delegate, MapFilter Filter) const
	{
		for (auto Pair : m_Map)
		{
			if (Filter(Pair.first, Pair.second))
			{
				Delegate(Pair.first, Pair.second);
			}
		}
	}

	template<typename TKey, typename TValue>
	INLINE decltype(auto) HashMap<TKey, TValue>::begin() const
	{
		m_Map.begin();
	}

	template<typename TKey, typename TValue>
	INLINE decltype(auto) HashMap<TKey, TValue>::end() const
	{
		m_Map.end();
	}
}


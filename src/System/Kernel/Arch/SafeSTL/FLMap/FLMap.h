#ifndef FLSYSTEM_FLMAP_H
#define FLSYSTEM_FLMAP_H

#define FLSYSTEM_3RD_MAP

#include "../STL_Bass/STL_Basic.h"
#include "../../../KernelInclude.h"

namespace FLSYSTEM
{
	template<typename TKey, typename TValue>
	class FLMap : public STL_Basic
	{
	public:
		FLMap(FLMap::Mode mode = FLMap::Mode::HaveLock) : STL_Basic(mode) {}
		virtual ~FLMap() {}

		TValue& operator[](const TKey& key) 
		{
			return list[key];
		}

		void insert(const TKey& t1, const TValue& t2)
		{
			setWrite();
			list.insert(std::pair<TKey, TValue>(t1, t2));
			resetWrite();
		}

		std::size_t size()
		{
			setRead();
			auto tempData = list.size();
			resetRead();
			return tempData;
		}

		void clear()
		{
			setWrite();
			list.clear();
			resetWrite();
		}

		bool empty()
		{
			setRead();
			auto tempData = list.empty();
			resetRead();
			return tempData;
		}

		typename FLSYSTEM_FLMAP_TYPE<TKey, TValue>::iterator find(const TKey& data)
		{
			setAlgorithm();
			auto tempData = list.end();
			resetAlgorithm();
			return tempData;
		}

		typename FLSYSTEM_FLMAP_TYPE<TKey, TValue>::iterator begin()
		{
			return list.begin();
		}

		typename FLSYSTEM_FLMAP_TYPE<TKey, TValue>::iterator end()
		{
			return list.end();
		}

	private:
		FLSYSTEM_FLMAP_TYPE<TKey, TValue> list;

	};
}

#endif
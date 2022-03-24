#ifndef FLSYSTEM_FLVECTOR_H
#define FLSYSTEM_FLVECTOR_H

#define FLSYSTEM_3RD_VECTOR

#include "../STL_Bass/STL_Basic.h"
#include "../../../PlatformInterface/PlatformInterface.h"

namespace FLSYSTEM
{
	template <typename T>
	class FLVector : public STL_Basic
	{
	private:
		std::vector<T> list;

	public:
		FLVector() : STL_Basic() {}
		virtual ~FLVector() {}

		T& operator[] (const std::size_t& pos)
		{
			setRead();
			auto tempData = list[pos];
			resetRead();
			return tempData;
		}

		void push_back(const T& data) noexcept
		{
			setWrite();
			list.push_back(data);
			resetWrite();
		}

		std::size_t size() noexcept
		{
			setRead();
			auto tempData = list.size();
			resetRead();
			return tempData;
		}

		void clear() noexcept
		{
			setWrite();
			list.clear();
			resetWrite();
		}

		bool empty() noexcept
		{
			setRead();
			auto tempData = list.empty();
			resetRead();
			return tempData;
		}

		typename std::vector<T>::iterator erase(typename std::vector<T>::const_iterator it) noexcept
		{
			setWrite();
			auto tempData = list.erase(it);
			resetWrite();
			return tempData;
		}

		typename std::vector<T>::iterator erase(typename std::vector<T>::const_iterator first, typename std::vector<T>::const_iterator last) noexcept
		{
			setWrite();
			auto tempData = list.erase(first, last);
			resetWrite();
			return tempData;
		}

		typename std::vector<T>::iterator begin() noexcept
		{
			return list.begin();
		}

		typename std::vector<T>::iterator end() noexcept
		{
			return list.end();
		}
	};
}

#endif
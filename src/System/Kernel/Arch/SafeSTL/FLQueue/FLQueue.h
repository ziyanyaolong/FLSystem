#ifndef FLSYSTEM_FLQUEUE_H
#define FLSYSTEM_FLQUEUE_H

#define FLSYSTEM_3RD_QUEUE

#include "../STL_Bass/STL_Basic.h"
#include "../../../KernelInclude.h"

namespace FLSYSTEM
{
	template<typename T>
	class FLQueue : public STL_Basic
	{
	private:
		FLSYSTEM_FLQUEUE_TYPE<T> queue;
		std::size_t max_size = 0;

	public:
		FLQueue(std::size_t number = 16, FLQueue::Mode mode = FLQueue::Mode::HaveLock) : STL_Basic(mode)
		{
			max_size = number;
		}

		virtual ~FLQueue()
		{
			clear();
		}

		bool push_back(const T& data)
		{
			setWrite();
			if (queue.size() >= max_size)
			{
				resetWrite();
				return false;
			}

			queue.push(data);
			resetWrite();
			return true;
		}

		std::size_t size()
		{
			setRead();
			auto tempData = queue.size();
			resetRead();
			return tempData;
		}

		void clear()
		{
			setWrite();
			while (!queue.empty())
			{
				queue.pop();
			}
			resetWrite();
		}

		bool empty()
		{
			setRead();
			auto tempData = queue.empty();
			resetRead();
			return tempData;                                
		}

		T peek()
		{
			setRead();
			auto tempData = queue.front();
			resetRead();
			      
			return tempData;
		}

		T read()
		{
			this->setWrite();
			auto tempData = queue.front();
			queue.pop();
			this->resetWrite();
			return tempData;
		}
	};
}

#endif
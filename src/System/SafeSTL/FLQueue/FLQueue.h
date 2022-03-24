#ifndef FLSYSTEM_FLQUEUE_H
#define FLSYSTEM_FLQUEUE_H

#define FLSYSTEM_3RD_QUEUE

#include "../STL_Bass/STL_Basic.h"
#include "../../../PlatformInterface/PlatformInterface.h"

#ifdef  FLSYSTEM_ARDUINO_BOARD
#include "../FLFRQueue/FLFRQueue.h"
#endif

namespace FLSYSTEM
{
	template <typename T>
	class FLQueue
#ifndef  FLSYSTEM_ARDUINO_BOARD
		: public STL_Basic
#else
		: public FLFRQueue<T>
#endif
	{
#ifndef  FLSYSTEM_ARDUINO_BOARD
	private:
		std::queue<T> queue;
		std::size_t max_size = 0;

	public:
		FLQueue(std::size_t number = 16) : STL_Basic()
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
#else
	public:
	FLQueue(std::size_t number = 16) : FLFRQueue<T>(number)
	{
	}

	virtual ~FLQueue()
	{
	}
#endif
	};
}

#endif
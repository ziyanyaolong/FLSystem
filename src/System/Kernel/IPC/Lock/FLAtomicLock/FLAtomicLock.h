#ifndef FLSYSTEM_FLATOMICLOCK_H
#define FLSYSTEM_FLATOMICLOCK_H

#define FLSYSTEM_3RD_ATOMIC

#include "../../../../../PlatformInterface/PlatformInterface.h"

#ifndef FLSYSTEM_ARDUINO_BOARD

namespace FLSYSTEM
{
    template <typename T>
	class FLAtomicLock
	{
	private:
		std::atomic<T> lock;

	public:
		FLAtomicLock(T data) { lock.store(data); }
		virtual ~FLAtomicLock() {}

		void procesOperables(T data)
		{
			set(data);
			operableData();
			reset(data);
		}

		virtual void operableData()
		{
		}

		T get()
		{
			return lock.load();
		}

		bool wait(T data, std::size_t number = 0)
		{
			T i = lock.load();
			std::size_t count = 0;

			while (true)
			{
				if (number != 0)
				{
					count++;
					if (count >= number)
					{
						return false;
					}
				}

				if (i == data)
				{
					i = lock.load();
					continue;
				}

				if (lock.compare_exchange_weak(i, data))
					break;

			}
			return true;
		}

		void direct(T data)
		{
			lock.store(data);
		}
	};
}
#endif

#endif
#ifndef FLSYSTEM_FLATOMICLOCK_H
#define FLSYSTEM_FLATOMICLOCK_H

#include "../LockInterface/AtomicInterface.h"
#include "../BaseLockInclude.h"
#include "../../../API/GC_API/GC_API.h"

namespace FLSYSTEM
{
    template <typename T>
	class FLAtomicLock : public GC_API
	{
	private:
		AtomicInterface<T>* _atomicLock = nullptr;

	public:
		explicit FLAtomicLock<T>(T data = T(), FLLockType type = FLLockType::Atomic) : GC_API()
		{
			_atomicLock = FLSYSTEM_TRANSPLANTATION_INSTANCE->createAtomic<T>(type);
		}

		virtual ~FLAtomicLock<T>() 
		{
			delete _atomicLock;
			_atomicLock = nullptr;
		}

		FLLockType typeGet()
		{
			return _atomicLock->typeGet();
		}

		bool isAtomic()
		{
			if (typeGet() == FLLockType::Atomic)
			{
				return true;
			}
			else
				return false;
		}

		T get() const
		{
			return _atomicLock->load();
		}

		bool wait(T data, unsigned long long number = UINT64_MAX)
		{
			T i = _atomicLock->load();
			unsigned long long count = 0;

			while (true)
			{
				if (number != UINT64_MAX)
				{
					count++;
					if (count >= number)
					{
						return false;
					}
				}

				if (i == data)
				{
					i = _atomicLock->load();
					continue;
				}

				if (_atomicLock->compare_exchange_strong(i, data))
					break;

			}
			return true;
		}
		
		void direct(T data)
		{
			return _atomicLock->store(data);
		}
	};
}

#endif
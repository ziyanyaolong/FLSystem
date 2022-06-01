#ifndef FLSYSTEM_FLLOCK_H
#define FLSYSTEM_FLLOCK_H

//#include "../FLAtomicLock_Bool/FLAtomicLock_Bool.h"
#include "../FLMutex/FLMutex.h"
#include "../FLAtomicLock_Bool/FLAtomicLock_Bool.h"
#include "../FLSemaphore/FLSemaphore.h"

namespace FLSYSTEM
{
	class FLLock
	{
	private:
		FLLockInterface* _lock = nullptr;
		bool createLock(FLLockType type);

	public:
		explicit FLLock(FLLockType type = FLLockType::Atomic);
		virtual ~FLLock();

		bool lock(unsigned long long time = UINT64_MAX);

		void unlock();

		bool isLocking();

		inline const FLLockType& typeGet()
		{
			return _lock->typeGet();
		}

		template<typename T>
		inline T* getLock()
		{
			return static_cast<T*>(_lock);
		}
	};
}

#endif

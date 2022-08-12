#ifndef FLSYSTEM_FLLOCK_H
#define FLSYSTEM_FLLOCK_H

#include "../BaseLockInclude.h"
#include "../FLMutex/FLMutex.h"
#include "../FLAtomicLock_Bool/FLAtomicLock_Bool.h"
#include "../FLSemaphore/FLSemaphore.h"
#include "../../../API/GC_API/GC_API.h"

namespace FLSYSTEM
{
	class FLLock : public GC_API
	{
	private:
		FLLockInterface* _lock = nullptr;
		bool createLock(FLLockType type);
		bool _isLocked = false;

	public:
		explicit FLLock(FLLockType type = FLLockType::Atomic);
		virtual ~FLLock();

		bool lock(unsigned long long time = UINT64_MAX);
		void unlock();

		inline FLLockType typeGet()
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

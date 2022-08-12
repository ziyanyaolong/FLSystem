#ifndef FLSYSTEM_FLSEMAPHORE_H
#define FLSYSTEM_FLSEMAPHORE_H

#include "../LockInterface/SemaphoreInterface.h"
#include "../BaseLockInclude.h"
#include "../../../API/GC_API/GC_API.h"

namespace FLSYSTEM
{
	class FLSemaphore : public FLLockInterface, public GC_API
	{
	private:
		SemaphoreInterface* _semaphore = nullptr;

		virtual bool lock_FLLock() override
		{
			return this->take();
		}

		virtual void unlock_FLLock() override
		{
			this->give();
		}

	public:
		explicit FLSemaphore(FLLockType type = FLLockType::Binary, unsigned long long maxCount = 1, unsigned long long initialCount = 0) : FLLockInterface(), GC_API()
		{
			_semaphore = FLSYSTEM_TRANSPLANTATION_INSTANCE->createSemaphore(type, maxCount, initialCount);
		}

		virtual ~FLSemaphore()
		{
			delete _semaphore;
			_semaphore = nullptr;
		}

		inline virtual FLLockType typeGet() const override
		{
			return _semaphore->typeGet();
		}

		inline bool take(unsigned long long  xTicksToWait = UINT64_MAX)
		{
			return _semaphore->take();
		}

		inline void give()
		{
			_semaphore->give();
		}

		inline bool isBinary()
		{
			if (_semaphore->typeGet() == FLLockType::Binary)
			{
				return true;
			}
			else
				return false;
		}

		inline bool isCounting()
		{
			if (_semaphore->typeGet() == FLLockType::Counting)
			{
				return true;
			}
			else
				return false;
		}

	};
}

#endif

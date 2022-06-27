#ifndef FLSYSTEM_SEMAPHORE_INTERFACE
#define FLSYSTEM_SEMAPHORE_INTERFACE

#include "LockBaseInterface.h"

namespace FLSYSTEM
{
	FLInterface SemaphoreInterface : public LockBaseInterface
	{
	protected:
		explicit SemaphoreInterface(FLLockType type, unsigned long long maxCount = 1, unsigned long long initialCount = 0) : LockBaseInterface(type) {}

	public:
		virtual ~SemaphoreInterface() {}

		virtual bool take(unsigned long long time = UINT64_MAX) = 0;
		virtual void give() = 0;
		virtual bool get() = 0;
	};
}

#endif

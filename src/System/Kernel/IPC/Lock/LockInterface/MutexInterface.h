#ifndef FLSYSTEM_MUTEX_INTERFACE_H
#define FLSYSTEM_MUTEX_INTERFACE_H

#include "LockBaseInterface.h"

namespace FLSYSTEM
{
	FLInterface MutexInterface : public LockBaseInterface
	{
	protected:
		explicit MutexInterface(FLLockType type) : LockBaseInterface(type) {}

	public:
		virtual ~MutexInterface() {}

		virtual bool lock(unsigned long long  xTicksToWait = UINT64_MAX) = 0;
		virtual void unlock() = 0;
	};
}

#endif

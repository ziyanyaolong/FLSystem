#ifndef FLSYSTEM_FLMUTEX_H
#define FLSYSTEM_FLMUTEX_H

#include "../../../../../PlatformInterface/PlatformInterface.h"
#include "../Interface/LockInterface.h"

namespace FLSYSTEM
{
	class FLMutex : public LockInterface
	{
	public:
		explicit FLMutex() : LockInterface() {}
		virtual ~FLMutex() {}

		virtual void lock() {}
		virtual void unlock() {}
		virtual bool isLocking() { return true; }

	};
}

#endif

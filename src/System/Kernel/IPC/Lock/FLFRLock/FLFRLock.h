#ifndef FLSYSTEM_FLFRLOCK_H
#define FLSYSTEM_FLFRLOCK_H

#include "../../../../../PlatformInterface/PlatformInterface.h"

#ifdef FLSYSTEM_3RD_FREERTOS

#include "../FLFRSemaphore/FLFRSemaphore.h"
#include "../Interface/LockInterface.h"

namespace FLSYSTEM
{
	class FLFRLock : public FLFRSemaphore, public LockInterface
	{
	private:

	public:
		explicit FLFRLock(FLFRSemaphore::Type type = FLFRSemaphore::Type::Mutex) : FLFRSemaphore(type), LockInterface() {}
		virtual ~FLFRLock() {}
		bool isLocking_ = false;

		virtual void lock()
		{
			take();
			isLocking_ = true;
		}

		virtual void unlock()
		{
			give();
			isLocking_ = false;
		}

		virtual bool isLocking()
		{
			return isLocking_;
		}
	};
}

#endif

#endif

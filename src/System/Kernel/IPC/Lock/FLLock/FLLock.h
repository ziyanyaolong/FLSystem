#ifndef FLSYSTEM_FLLOCK_H
#define FLSYSTEM_FLLOCK_H

#include "../FLAtomicLock_Bool/FLAtomicLock_Bool.h"
#include "../FLMutex/FLMutex.h"
#include "../Interface/LockInterface.h"
#include "../FLFRLock/FLFRLock.h"

namespace FLSYSTEM
{
	class FLLock : public LockInterface
	{
	private:
		LockInterface* flLock = nullptr;

	public:
		enum class Type
		{
			Atomic,
			Binary,
			Counting,
			Mutex,
			RecursiveMutex
		};

		explicit FLLock(FLLock::Type type = FLLock::Type::Atomic);
		virtual ~FLLock();

		virtual void lock()
		{
			flLock->lock();
		}

		virtual void unlock()
		{
			flLock->unlock();
		}

		virtual bool isLocking()
		{
			return flLock->isLocking();
		}

	};
}

#endif

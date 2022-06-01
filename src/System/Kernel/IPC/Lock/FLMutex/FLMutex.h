#ifndef FLSYSTEM_FLMUTEX_H
#define FLSYSTEM_FLMUTEX_H

#include "../LockInterface/MutexInterface.h"
#include "../LockInterface/FLLockInterface.h"
#include "../../../../../PlatformInterface/PlatformInterface.h"

namespace FLSYSTEM
{
	class FLMutex : public FLLockInterface
	{
	private:
		MutexInterface* _mutex = nullptr;

		inline virtual bool lock_FLLock() override
		{
			return this->lock();
		}

		inline virtual void unlock_FLLock() override
		{
			this->unlock();
		}

		inline virtual bool isLocking_FLLock() override
		{
			return this->isLocking();
		}

	public:
		explicit FLMutex(FLLockType type = FLLockType::Mutex) : FLLockInterface()
		{
			_mutex = FLSYSTEM_TRANSPLANTATION_INSTANCE->createMutex(type);
		}

		virtual ~FLMutex() 
		{
			delete _mutex;
			_mutex = nullptr;
		}

		inline virtual FLLockType typeGet() override
		{
			return _mutex->typeGet();
		}

		inline bool lock(unsigned long long  xTicksToWait = UINT64_MAX) { return _mutex->lock(xTicksToWait); }
		inline void unlock() { _mutex->unlock(); }
		inline bool isLocking() { return _mutex->isLocking(); }

		inline bool isMutex()
		{
			if (_mutex->typeGet() == FLLockType::Mutex)
			{
				return true;
			}
			else
				return false;
		}

		inline bool isRecursiveMutex()
		{
			if (_mutex->typeGet() == FLLockType::RecursiveMutex)
			{
				return true;
			}
			else
				return false;
		}

	};
}

#endif

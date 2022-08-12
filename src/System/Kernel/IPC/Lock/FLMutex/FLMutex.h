#ifndef FLSYSTEM_FLMUTEX_H
#define FLSYSTEM_FLMUTEX_H

#include "../LockInterface/MutexInterface.h"
#include "../BaseLockInclude.h"
#include "../../../API/GC_API/GC_API.h"

namespace FLSYSTEM
{
	class FLMutex : public FLLockInterface, public GC_API
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

		void createMutex(FLLockType type)
		{
			_mutex = FLSYSTEM_TRANSPLANTATION_INSTANCE->createMutex(type);
		}

		FLMutex& deepCopy(const FLMutex& flMutex)
		{
			if (this->_mutex)
			{
				_mutex->unlock();

				delete _mutex;

				if (flMutex._mutex)
				{
					this->createMutex(flMutex.typeGet());
				}
			}

			return *this;
		}

	public:
		explicit FLMutex() : FLLockInterface(), GC_API()
		{
		}

		explicit FLMutex(FLLockType type) : FLLockInterface(), GC_API()
		{
			this->createMutex(type);
		}

		virtual ~FLMutex()
		{
			if (_mutex)
			{
				_mutex->unlock();
				delete _mutex;
				_mutex = nullptr;
			}
		}

		inline virtual FLLockType typeGet() const override
		{
			return _mutex->typeGet();
		}

		inline bool lock(unsigned long long  xTicksToWait = UINT64_MAX) { return _mutex->lock(xTicksToWait); }
		inline void unlock() { _mutex->unlock(); }

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

		FLMutex(const FLMutex& flMutex)
		{
			this->deepCopy(flMutex);
		}

		FLMutex(const FLMutex&& flMutex)
		{
			this->deepCopy(flMutex);
		}

		FLMutex& operator=(const FLMutex& flMutex)
		{
			return this->deepCopy(flMutex);
		}
	};
}

#endif

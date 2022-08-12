#ifndef FLSYSTEM_FLATOMICLOCK_BOOL_H
#define FLSYSTEM_FLATOMICLOCK_BOOL_H

#include "../FLAtomicLock/FLAtomicLock.h"

namespace FLSYSTEM
{
	class FLAtomicLock_Bool : public FLAtomicLock<bool>, public FLLockInterface
	{
	private:
		inline virtual bool lock_FLLock() override
		{
			return this->lock();
		}

		inline virtual void unlock_FLLock() override
		{
			this->unlock();
		}

	public:
		FLAtomicLock_Bool() : FLAtomicLock<bool>(false), FLLockInterface() {}
		virtual ~FLAtomicLock_Bool() {}

		enum class LockWay
		{
			Wait,
			Direct
		};

		inline virtual FLLockType typeGet() const override
		{
			return typeGet();
		}

		bool lock(LockWay way = LockWay::Wait, unsigned long long number = UINT64_MAX)
		{
			switch (way)
			{
			case FLAtomicLock_Bool::LockWay::Wait:
				return this->wait(true, number);
				break;

			case FLAtomicLock_Bool::LockWay::Direct:
				this->direct(true);
				return true;
				break;

			default:
				return false;
				break;
			}
			return false;
		}

		bool unlock(LockWay way = LockWay::Direct, unsigned long long number = UINT64_MAX)
		{
			switch (way)
			{
			case FLAtomicLock_Bool::LockWay::Wait:
				return this->wait(false, number);
				break;

			case FLAtomicLock_Bool::LockWay::Direct:
				this->direct(false);
				return true;
				break;

			default:
				return false;
				break;
			}
			return false;
		}
	};
}

#endif
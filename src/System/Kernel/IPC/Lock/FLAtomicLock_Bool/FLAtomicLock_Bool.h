#ifndef FLSYSTEM_FLATOMICLOCK_BOOL_H
#define FLSYSTEM_FLATOMICLOCK_BOOL_H

#include "../FLAtomicLock/FLAtomicLock.h"
#include "../Interface/LockInterface.h"

#ifndef FLSYSTEM_ARDUINO_BOARD

namespace FLSYSTEM
{
    class FLAtomicLock_Bool : public LockInterface, public FLAtomicLock<bool>
	{
	public:
		FLAtomicLock_Bool() : LockInterface(), FLAtomicLock<bool>(false) {}
		virtual ~FLAtomicLock_Bool() {}
		enum class LockWay
		{
			Wait,
			Direct
		};

		bool lock(LockWay way, std::size_t number = 0)
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

		bool unlock(LockWay way, std::size_t number = 0)
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

		virtual void lock()
		{
			lock(LockWay::Wait);
		}

		virtual void unlock()
		{
			unlock(LockWay::Direct);
		}

		virtual bool isLocking()
		{
			return get();
		}
	};
}
#endif

#endif
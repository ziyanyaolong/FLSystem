#include "FLLock.h"

FLSYSTEM::FLLock::FLLock(FLLockType type)
{
	if (!createLock(type))
	{
		FLSYSTEM_TRANSPLANTATION_INSTANCE->exception("Create Lock Fail!");
	}
}

FLSYSTEM::FLLock::~FLLock()
{
	if (_lock)
	{
		delete _lock;
	}
}

bool FLSYSTEM::FLLock::createLock(FLSYSTEM::FLLockType type)
{
	if (_lock)
	{
		delete _lock;
	}

	switch (type)
	{
	case FLSYSTEM::FLLockType::UnknowType:
		return (bool)(_lock = new FLSYSTEM::FLAtomicLock_Bool());
		break;

	case FLSYSTEM::FLLockType::Atomic:
		return (bool)(_lock = new FLSYSTEM::FLAtomicLock_Bool());
		break;

	case FLSYSTEM::FLLockType::Binary:
		return (bool)(_lock = new FLSYSTEM::FLSemaphore(FLSYSTEM::FLLockType::Binary));
		break;

	case FLSYSTEM::FLLockType::Counting:
		return (bool)(_lock = new FLSYSTEM::FLSemaphore(FLSYSTEM::FLLockType::Counting));

		break;

	case FLSYSTEM::FLLockType::Mutex:
		return (bool)(_lock = new FLSYSTEM::FLMutex(FLSYSTEM::FLLockType::Mutex));

		break;

	case FLSYSTEM::FLLockType::RecursiveMutex:
		return (bool)(_lock = new FLSYSTEM::FLMutex(FLSYSTEM::FLLockType::RecursiveMutex));
		break;

	default:
		return false;
		break;
	}
	return false;
}

bool FLSYSTEM::FLLock::lock(unsigned long long time)
{
	return _lock->lock_FLLock();
}

void FLSYSTEM::FLLock::unlock()
{
	_lock->unlock_FLLock();
}

bool FLSYSTEM::FLLock::isLocking()
{
	return _lock->isLocking_FLLock();
}
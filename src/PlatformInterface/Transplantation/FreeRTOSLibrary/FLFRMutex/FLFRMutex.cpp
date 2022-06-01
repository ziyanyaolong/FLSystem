#include "FLFRMutex.h"

#ifdef FLSYSTEM_ENABLE_FREERTOS_LIBRARY

FLSYSTEM::FLFRMutex::FLFRMutex(FLLockType type) : MutexInterface(type)
{
	switch (type)
	{
	case FLSYSTEM::FLLockType::Mutex:
		_mutex = xSemaphoreCreateMutex();
		break;

	case FLSYSTEM::FLLockType::RecursiveMutex:
		_mutex = xSemaphoreCreateRecursiveMutex();
		break;

	default:
		break;
	}

	if (_mutex == nullptr)
	{
		return;
	}
}

inline bool FLSYSTEM::FLFRMutex::lock(unsigned long long xTicksToWait)
{
	switch (this->typeGet())
	{
	case FLSYSTEM::FLLockType::Mutex:
		return xSemaphoreTake(_mutex, (TickType_t)xTicksToWait);
		break;

	case FLSYSTEM::FLLockType::RecursiveMutex:
		return xSemaphoreTakeRecursive(_mutex, (TickType_t)xTicksToWait);
		break;

	default:
		return false;
		break;
	}

	_isLocking = true;
}

inline void FLSYSTEM::FLFRMutex::unlock()
{
	switch (this->typeGet())
	{
	case FLSYSTEM::FLLockType::Mutex:
		xSemaphoreGive(_mutex);
		break;

	case FLSYSTEM::FLLockType::RecursiveMutex:
		xSemaphoreGiveRecursive(_mutex);
		break;

	default:
		break;
	}

	_isLocking = false;
}

inline bool FLSYSTEM::FLFRMutex::isLocking()
{
	return _isLocking;
}

FLSYSTEM::FLFRMutex::~FLFRMutex()
{
	if (_mutex)
	{
		unlock();
		vSemaphoreDelete(_mutex);
	}
}

#endif
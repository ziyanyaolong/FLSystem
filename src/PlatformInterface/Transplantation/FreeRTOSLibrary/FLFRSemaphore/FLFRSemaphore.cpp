#include "FLFRSemaphore.h"

#ifdef FLSYSTEM_ENABLE_FREERTOS_LIBRARY

FLSYSTEM::FLFRSemaphore::FLFRSemaphore(FLLockType type, UBaseType_t uxMaxCount, UBaseType_t uxInitialCount) : SemaphoreInterface(type)
{
	switch (type)
	{
	case FLSYSTEM::FLLockType::Binary:
		_semaphore = xSemaphoreCreateBinary();
		break;

	case FLSYSTEM::FLLockType::Counting:
		_semaphore = xSemaphoreCreateCounting(uxMaxCount, uxInitialCount);
		break;

	default:
		break;
	}

	if (_semaphore == nullptr)
	{
		return;
	}
}

FLSYSTEM::FLFRSemaphore::~FLFRSemaphore()
{
	if (_semaphore)
	{
		this->take();
		vSemaphoreDelete(_semaphore);
	}
}

inline bool FLSYSTEM::FLFRSemaphore::take(unsigned long long  xTicksToWait)
{
	switch (this->typeGet())
	{
	case FLSYSTEM::FLLockType::Binary:
		return xSemaphoreTake(_semaphore, (TickType_t)xTicksToWait);
		break;

	case FLSYSTEM::FLLockType::Counting:
		return xSemaphoreTake(_semaphore, (TickType_t)xTicksToWait);
		break;

	default:
		return false;
		break;
	}
}

inline void FLSYSTEM::FLFRSemaphore::give()
{
	switch (this->typeGet())
	{
	case FLSYSTEM::FLLockType::Binary:
		xSemaphoreGive(_semaphore);
		break;

	case FLSYSTEM::FLLockType::Counting:
		xSemaphoreGive(_semaphore);
		break;

	default:
		break;
	}
}

inline bool FLSYSTEM::FLFRSemaphore::giveFromISR(BaseType_t* const pxHigherPriorityTaskWoken)
{
	return xSemaphoreGiveFromISR(_semaphore, pxHigherPriorityTaskWoken);
}

inline bool FLSYSTEM::FLFRSemaphore::takeFromISR(BaseType_t* const pxHigherPriorityTaskWoken)
{
	return xSemaphoreTakeFromISR(_semaphore, pxHigherPriorityTaskWoken);
}

#endif
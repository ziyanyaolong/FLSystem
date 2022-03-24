#include "FLFRSemaphore.h"

#ifdef FLSYSTEM_3RD_FREERTOS

FLSYSTEM::FLFRSemaphore::FLFRSemaphore(FLFRSemaphore::Type type, UBaseType_t uxMaxCount, UBaseType_t uxInitialCount)
{
	_type = type;

	switch (type)
	{
	case FLSYSTEM::FLFRSemaphore::Type::Binary:
		semaphore = xSemaphoreCreateBinary();
		break;

	case FLSYSTEM::FLFRSemaphore::Type::Counting:
		semaphore = xSemaphoreCreateCounting(uxMaxCount, uxInitialCount);
		break;

	case FLSYSTEM::FLFRSemaphore::Type::Mutex:
		semaphore = xSemaphoreCreateMutex();
		break;

	case FLSYSTEM::FLFRSemaphore::Type::RecursiveMutex:
		semaphore = xSemaphoreCreateRecursiveMutex();
		break;

	default:
		break;
	}

	if (semaphore == nullptr)
	{
		FLException("create semaphore error!");
	}
}

FLSYSTEM::FLFRSemaphore::~FLFRSemaphore()
{
	if (semaphore)
	{
		take();
		vSemaphoreDelete(semaphore);
	}
}

bool FLSYSTEM::FLFRSemaphore::isRecursiveMutex()
{
	if(_type == FLFRSemaphore::Type::RecursiveMutex)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool FLSYSTEM::FLFRSemaphore::isBinary()
{
	if (_type == FLFRSemaphore::Type::Binary)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool FLSYSTEM::FLFRSemaphore::isCounting()
{
	if (_type == FLFRSemaphore::Type::Counting)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool FLSYSTEM::FLFRSemaphore::isMutex()
{
	if (_type == FLFRSemaphore::Type::Mutex || _type == FLFRSemaphore::Type::RecursiveMutex)
	{
		return true;
	}
	else
	{
		return false;
	}
}

UBaseType_t FLSYSTEM::FLFRSemaphore::getCount()
{
	if (isMutex() || isRecursiveMutex())
	{
		return 0;
	}

	return uxSemaphoreGetCount(semaphore);
}

bool FLSYSTEM::FLFRSemaphore::give()
{
	switch (_type)
	{
	case FLSYSTEM::FLFRSemaphore::Type::Binary:
		return xSemaphoreGive(semaphore);
		break;

	case FLSYSTEM::FLFRSemaphore::Type::Counting:
		return xSemaphoreGive(semaphore);
		break;

	case FLSYSTEM::FLFRSemaphore::Type::Mutex:
		return xSemaphoreGive(semaphore);
		break;

	case FLSYSTEM::FLFRSemaphore::Type::RecursiveMutex:
		return xSemaphoreGiveRecursive(semaphore);
		break;

	default:
		break;
	}
}

bool FLSYSTEM::FLFRSemaphore::take(TickType_t xTicksToWait)
{

	switch (_type)
	{
	case FLSYSTEM::FLFRSemaphore::Type::Binary:
		return xSemaphoreTake(semaphore, xTicksToWait);
		break;

	case FLSYSTEM::FLFRSemaphore::Type::Counting:
		return xSemaphoreTake(semaphore, xTicksToWait);
		break;

	case FLSYSTEM::FLFRSemaphore::Type::Mutex:
		return xSemaphoreTake(semaphore, xTicksToWait);
		break;

	case FLSYSTEM::FLFRSemaphore::Type::RecursiveMutex:
		return xSemaphoreTakeRecursive(semaphore, xTicksToWait);
		break;

	default:
		break;
	}
}

bool FLSYSTEM::FLFRSemaphore::giveFromISR(BaseType_t* const pxHigherPriorityTaskWoken)
{
	return xSemaphoreGiveFromISR(semaphore, pxHigherPriorityTaskWoken);
}

bool FLSYSTEM::FLFRSemaphore::takeFromISR(BaseType_t* const pxHigherPriorityTaskWoken)
{
	return xSemaphoreTakeFromISR(semaphore, pxHigherPriorityTaskWoken);
}

#endif
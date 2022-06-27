#include "FLDFSemaphore.h"

#ifdef FLSYSTEM_ENABLE_DEFAULT_LIBRARY

FLSYSTEM::FLDFSemaphore::FLDFSemaphore(FLLockType type, unsigned long long maxCount, unsigned long long initialCount) : SemaphoreInterface(type), _mutex(new FLDFMutex(FLLockType::Mutex)), count((long)initialCount)
{
	if (type == FLLockType::Counting)
	{
		_semaphoreData = new SemaphoreData();
		_semaphoreData->maxCount = maxCount;
		_semaphoreData->initialCount = initialCount;
	}
}

FLSYSTEM::FLDFSemaphore::~FLDFSemaphore()
{
	if (_mutex)
	{
		delete _mutex;
		_mutex = nullptr;
	}

	if (_semaphoreData)
	{
		delete _semaphoreData;
		_semaphoreData = nullptr;
	}
}

inline void FLSYSTEM::FLDFSemaphore::give()
{
	if ((count >= _semaphoreData->maxCount) || (count == 0))
	{
		return;
	}

	_mutex->lock();

	++count;

	if (count != 0)
	{
		_mutex->unlock();
		cond.notify_one();
	}
}

inline bool FLSYSTEM::FLDFSemaphore::take(unsigned long long time)
{
	_mutex->lock();

	--count;

	if (count < 0)
	{
		_mutex->unlock();
		switch (cond.wait_for(*(_mutex->getLockFor<std::timed_mutex*>()), std::chrono::milliseconds(time)))
		{
		case std::cv_status::no_timeout:
			return true;
			break;

		case std::cv_status::timeout:
			return false;
			break;

		default:
			break;
		}
	}

	_mutex->unlock();

	return false;
}

inline bool FLSYSTEM::FLDFSemaphore::get()
{
	if (count != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

#endif
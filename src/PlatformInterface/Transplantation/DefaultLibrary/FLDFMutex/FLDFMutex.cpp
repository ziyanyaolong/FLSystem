#include "FLDFMutex.h"

#ifdef FLSYSTEM_ENABLE_DEFAULT_LIBRARY

FLSYSTEM::FLDFMutex::FLDFMutex(FLLockType type) : MutexInterface(type)
{
	switch (type)
	{
	case FLSYSTEM::FLLockType::UnknowType:
		_mutex = new std::timed_mutex();
		break;
	case FLSYSTEM::FLLockType::Mutex:
		_mutex = new std::timed_mutex();
		break;
	case FLSYSTEM::FLLockType::RecursiveMutex:
		_mutex = new std::recursive_timed_mutex();
		break;
	default:
		break;
	}
}

inline bool FLSYSTEM::FLDFMutex::lock(unsigned long long  time)
{
	switch (typeGet())
	{
	case FLSYSTEM::FLLockType::UnknowType:
		if (time == UINT64_MAX)
		{
			static_cast<std::timed_mutex*>(_mutex)->lock();
		}
		else
		{
			if (!(static_cast<std::timed_mutex*>(_mutex)->try_lock_for(std::chrono::milliseconds(time))))
			{
				return false;
			}
		}
		_isLooking = true;
		return true;
		break;
	case FLSYSTEM::FLLockType::Mutex:
		if (time == UINT64_MAX)
		{
			static_cast<std::timed_mutex*>(_mutex)->lock();
		}
		else
		{
			if (!(static_cast<std::timed_mutex*>(_mutex)->try_lock_for(std::chrono::milliseconds(time))))
			{
				return false;
			}
		}
		_isLooking = true;
		return true;
		break;
	case FLSYSTEM::FLLockType::RecursiveMutex:
		if (time == UINT64_MAX)
		{
			static_cast<std::recursive_timed_mutex*>(_mutex)->lock();
		}
		else
		{
			if (!(static_cast<std::recursive_timed_mutex*>(_mutex)->try_lock_for(std::chrono::milliseconds(time))))
			{
				return false;
			}
		}
		_isLooking = true;
		return true;
		break;
	default:
		break;
	}

	return false;
}

inline void FLSYSTEM::FLDFMutex::unlock()
{
	switch (typeGet())
	{
	case FLSYSTEM::FLLockType::UnknowType:
		(static_cast<std::timed_mutex*>(_mutex))->unlock();
		break;
	case FLSYSTEM::FLLockType::Mutex:
		(static_cast<std::timed_mutex*>(_mutex))->unlock();
		break;
	case FLSYSTEM::FLLockType::RecursiveMutex:
		(static_cast<std::recursive_timed_mutex*>(_mutex))->unlock();
		break;
	default:
		break;
	}

	_isLooking = false;
}

inline bool FLSYSTEM::FLDFMutex::isLocking()
{
	return _isLooking;
}

inline void* FLSYSTEM::FLDFMutex::getLock()
{
	return _mutex;
}

#endif
#include "FLLock.h"

FLSYSTEM::FLLock::FLLock(FLLock::Type type) : LockInterface()
{
	switch (type)
	{
	case FLSYSTEM::FLLock::Type::Atomic:
#ifndef FLSYSTEM_ARDUINO_BOARD
		flLock = new FLAtomicLock_Bool();
#else
		flLock = new FLFRLock(FLFRLock::Type::RecursiveMutex);
#endif
		break;

	case FLSYSTEM::FLLock::Type::Binary:
#ifndef FLSYSTEM_ARDUINO_BOARD
		flLock = new FLMutex();
#else
		flLock = new FLFRLock(FLFRLock::Type::Binary);
#endif
		break;

	case FLSYSTEM::FLLock::Type::Counting:
#ifndef FLSYSTEM_ARDUINO_BOARD
		flLock = new FLMutex();
#else
		flLock = new FLFRLock(FLFRLock::Type::Counting);
#endif
		break;

	case FLSYSTEM::FLLock::Type::Mutex:
#ifndef FLSYSTEM_ARDUINO_BOARD
		flLock = new FLMutex();
#else
		flLock = new FLFRLock(FLFRLock::Type::Mutex);
#endif
		break;

	case FLSYSTEM::FLLock::Type::RecursiveMutex:
#ifndef FLSYSTEM_ARDUINO_BOARD
		flLock = new FLMutex();
#else
		flLock = new FLFRLock(FLFRLock::Type::RecursiveMutex);
#endif
		break;

	default:
		break;
	}
}

FLSYSTEM::FLLock::~FLLock()
{
	if (flLock)
	{
		delete flLock;
	}
}
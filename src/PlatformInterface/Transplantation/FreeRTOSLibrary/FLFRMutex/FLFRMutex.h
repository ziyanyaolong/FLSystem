#ifndef FLSYSTEM_FLFRMUTEX_H
#define FLSYSTEM_FLFRMUTEX_H

#include "../../../FLTRSwitch.h"

#ifdef FLSYSTEM_ENABLE_FREERTOS_LIBRARY

#include "../../FLTRInclude.h"

#define FLSYSTEM_3RD_FREERTOS

#include "../../../3rdInclude.h"

namespace FLSYSTEM
{
	class FLFRMutex : public MutexInterface
	{
	private:
		SemaphoreHandle_t _mutex = nullptr;

	public:
		explicit FLFRMutex(FLLockType type = FLLockType::Mutex);
		virtual ~FLFRMutex();

		virtual bool lock(unsigned long long  xTicksToWait = UINT64_MAX) override;
		virtual void unlock() override;

	};
}

#endif

#endif

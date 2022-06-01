#ifndef FLSYSTEM_FLDFMUTEX_H
#define FLSYSTEM_FLDFMUTEX_H

#include "../../../FLTRSwitch.h"

#ifdef FLSYSTEM_ENABLE_DEFAULT_LIBRARY

#include "../../FLTRInclude.h"

#define FLSYSTEM_3RD_MUTEX

#include "../../../3rdInclude.h"

namespace FLSYSTEM
{
	class FLDFMutex : public MutexInterface
	{
	private:
		void* _mutex = nullptr;
		bool _isLooking = false;

	public:
		explicit FLDFMutex(FLLockType type = FLLockType::Mutex);
		virtual ~FLDFMutex() {}

		virtual bool lock(unsigned long long time = UINT64_MAX) override;
		virtual void unlock() override;
		virtual bool isLocking() override;
		virtual void* getLock() override;
	};
}

#endif

#endif

#ifndef FLSYSTEM_FLDFSEMAPHORE_H
#define FLSYSTEM_FLDFSEMAPHORE_H

#include "../../../FLTRSwitch.h"

#ifdef FLSYSTEM_ENABLE_DEFAULT_LIBRARY

#include "../../FLTRInclude.h"

#include "../FLDFMutex/FLDFMutex.h"

#define FLSYSTEM_3RD_CONDITION_VARIABLE

#include "../../../3rdInclude.h"

namespace FLSYSTEM
{
	class FLDFSemaphore : public SemaphoreInterface
	{
	private:
		struct SemaphoreData
		{
			unsigned long long maxCount = 1;
			unsigned long long initialCount = 0;
		};

		FLDFMutex* _mutex;
		std::condition_variable_any cond;
		long count = 0;
		bool isLock = false;
		
		SemaphoreData* _semaphoreData = nullptr;

	public:
		explicit FLDFSemaphore(FLLockType type = FLLockType::Binary, unsigned long long maxCount = 1, unsigned long long initialCount = 0);

		virtual ~FLDFSemaphore();

		virtual void give() override;
		virtual bool take(unsigned long long time = UINT64_MAX) override;
		virtual bool get() override;
	};
}

#endif

#endif
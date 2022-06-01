#ifndef FLSYSTEM_DEFAULTLIBRARY_H
#define FLSYSTEM_DEFAULTLIBRARY_H

#include "../../FLTRSwitch.h"

#ifdef FLSYSTEM_ENABLE_DEFAULT_LIBRARY

#include "FLDFMutex/FLDFMutex.h"
#include "FLDFSemaphore/FLDFSemaphore.h"
#include "FLDFAtomic/FLDFAtomic.h"

#include "../StandardAPI/StandardAPI.h"

#define FLSYSTEM_3RD_IOSTREAM

#include "../../3rdInclude.h"

namespace FLSYSTEM
{
	class DefaultLibrary : public StandardAPI<DefaultLibrary>
	{
	public:
		explicit DefaultLibrary() : StandardAPI<DefaultLibrary>() {}
		virtual ~DefaultLibrary() {}

		struct DefaultConfig
		{
			const unsigned long long maxDelay = UINT64_MAX;
		};

		struct ThreadConfig
		{
			typedef void (*_ThreadFun_)(void*);
			_ThreadFun_ threadCode = nullptr;
			const char* const name = "";
			unsigned short stackDepth = 1024;
			void* parameters = nullptr;
			unsigned long priority = 1;
			void** pxCreatedThread = nullptr;
			short coreID = 0;
			unsigned long long runTimeDelay = 1;
			long returned = 0;
			void* threadClass = nullptr;
		};

		long fl_createThread(void* data)
		{
			auto pConfig = static_cast<ThreadConfig*>(data);

			if (pConfig == nullptr || pConfig->threadCode == nullptr)
			{
				this->exception("Error:Not the correct configuration file.");
				return 0;
			}
			std::thread* mthread = new std::thread(pConfig->threadCode, data);
			mthread->detach();
			pConfig->pxCreatedThread = reinterpret_cast<void** const>(&mthread);
			if (mthread == nullptr)
			{
				return 0;
			}

			return 1;
		}

		void fl_exitThread(void* pointer)
		{
			while (true)
			{
				fl_threadDelay(INT64_MAX);
			}
		}

		void fl_threadDelay(long long time)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(time));
		}

		void fl_debugPrint(const char* str, void* data = nullptr)
		{
			std::cout << "Line:" << __LINE__ << ",FileName:" << __FILE__ << ",Debug:" << str;
		}

		template <typename _Ty>
		inline AtomicInterface<_Ty>* fl_createAtomic(FLLockType type)
		{
			return static_cast<AtomicInterface<_Ty>*>(new FLDFAtomic<_Ty>(type));
		}

		inline MutexInterface* fl_createMutex(FLLockType type)
		{
			return static_cast<MutexInterface*>(new FLDFMutex(type));
		}

		inline SemaphoreInterface* fl_createSemaphore(FLLockType type, unsigned long long maxCount = 1, unsigned long long initialCount = 0)
		{
			return static_cast<SemaphoreInterface*>(new FLDFSemaphore(type, maxCount, initialCount));
		}

	};
}

#endif

#endif
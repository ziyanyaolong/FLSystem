#ifndef FLSYSTEM_DEFAULTLIBRARY_H
#define FLSYSTEM_DEFAULTLIBRARY_H

#include "../../FLTRSwitch.h"

#ifdef FLSYSTEM_ENABLE_DEFAULT_LIBRARY

#include "FLDFMutex/FLDFMutex.h"
#include "FLDFSemaphore/FLDFSemaphore.h"
#include "FLDFAtomic/FLDFAtomic.h"

#include "../StandardAPI/StandardAPI.h"

#define FLSYSTEM_3RD_IOSTREAM

#ifdef FLSYSTEM_ENABLE_LVGL_MEMORY_MANAGEMENT
#define FLSYSTEM_3RD_LVGL
#endif

#include "../../3rdInclude.h"

#define FLSYSTEM_FLVECTOR_TYPE FLSYSTEM_FLVECTOR_TYPE_DEFINE
#define FLSYSTEM_FLLIST_TYPE FLSYSTEM_FLLIST_TYPE_DEFINE
#define FLSYSTEM_FLQUEUE_TYPE FLSYSTEM_FLQUEUE_TYPE_DEFINE
#define FLSYSTEM_FLMAP_TYPE FLSYSTEM_FLMAP_TYPE_DEFINE

namespace FLSYSTEM
{
	class DefaultLibrary : public StandardAPI<DefaultLibrary>
	{
	public:
		explicit DefaultLibrary() : StandardAPI<DefaultLibrary>() {}
		virtual ~DefaultLibrary() {}

		struct DefaultConfig
		{
			static const unsigned long long maxDelay = UINT32_MAX;
		};

		struct ThreadConfig
		{
			typedef void (*_ThreadFun_)(void*);
			_ThreadFun_ threadCode = nullptr;
			const char* const name = "";
			unsigned long stackDepth = 1024;
			void* parameters = nullptr;
			unsigned long priority = 1;
			std::thread* createdThread = nullptr;
			short coreID = 0;
			unsigned long long runTimeDelay = 50;
			long returned = 0;
			void* threadClass = nullptr;
			FLDFAtomic<bool> threadExit_Bool;
			void* userData = nullptr;
		};

		static void _thread_run_func_(ThreadConfig* data)
		{
			while (!(data->threadExit_Bool.load()))
			{
				data->threadCode(data);
				break;
			}
		}

		long fl_createThread(void* data)
		{
			auto pConfig = static_cast<ThreadConfig*>(data);

			if (pConfig == nullptr || pConfig->threadCode == nullptr)
			{
				this->exception("Error:Not the correct configuration file.");
				return 0;
			}

			pConfig->threadExit_Bool.store(false);
			std::thread* mthread = new std::thread(&DefaultLibrary::_thread_run_func_, pConfig);
			mthread->detach();
			pConfig->createdThread = mthread;
			if (mthread == nullptr)
			{
				return 0;
			}

			return 1;
		}

		void fl_exitThread(void* pointer)
		{
			auto pConfig = static_cast<ThreadConfig*>(pointer);

			if (pConfig == nullptr || pConfig->createdThread == nullptr)
			{
				this->exception("Error:Not the correct configuration file.");
				return;
			}

			pConfig->threadExit_Bool.store(true);
		}

		void fl_threadDelay(void* timeData)
		{
			auto pConfig = static_cast<ThreadDelayConfig*>(timeData);

			if (pConfig == nullptr)
			{
				this->exception("Error:Not the correct configuration file.");
				return;
			}

			if (pConfig->threadConfig == nullptr)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(pConfig->time));
				return;
			}
			else
			{
				long long time = 0;
				while (!(pConfig->threadConfig->threadExit_Bool.load()))
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
					time++;

					if (time >= long long(pConfig->time / 2))
					{
						break;
					}
				}
			}

			return;
		}

		void fl_debug(const char* str, void* data = nullptr)
		{
			std::cout << "Line:" << __LINE__ << ",FileName:" << __FILE__ << ",Debug:" << str;
		}

		template <typename _Ty, typename ... _Args>
		inline AtomicInterface<_Ty>* fl_createAtomic(FLLockType type, _Args ... args)
		{
			return static_cast<AtomicInterface<_Ty>*>(new FLDFAtomic<_Ty>(type, args...));
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
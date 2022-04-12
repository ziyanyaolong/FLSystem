#ifndef FLSYSTEM_$capitalsafeitemname$_H
#define FLSYSTEM_$capitalsafeitemname$_H

#include "../../TransplantationInterface/TransplantationInterface.h"

#ifdef FLSYSTEM_3RD_THREAD

namespace FLSYSTEM
{
	class StandardLibrary : public TransplantationInterface
	{
	public:
		explicit StandardLibrary() {}
		virtual ~StandardLibrary() {}

		struct TaskConfig
		{
			typedef void (*_TaskFun_)(void*);
			_TaskFun_ taskCode = nullptr;
			const char* const name = "";
			unsigned short stackDepth = 1024;
			void* parameters = nullptr;
			unsigned long priority = 1;
			void** pxCreatedTask = nullptr;
			short coreID = 0;
			unsigned long long runTimeDelay = 1;
			long returned = 0;
			void* threadClass = nullptr;
		};

		virtual long createTask(void* data) override
		{
			auto pConfig = static_cast<TaskConfig*>(data);

			if (pConfig == nullptr || pConfig->taskCode == nullptr)
			{
				this->exception("Error:Not the correct configuration file.");
				return 0;
			}
			std::thread* mthread = new std::thread(pConfig->taskCode, data);
			mthread->detach();
			pConfig->pxCreatedTask = reinterpret_cast<void** const>(&mthread);
			if (mthread == nullptr)
			{
				return 0;
			}

			return 1;
		}

		virtual void exitTask(void* pointer) override
		{
			this->taskDelay(0);
		}

		virtual void taskDelay(long long time) override
		{
			if (time <= 0)
			{
				while (1)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				}
			}
			else
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(time));
			}
		}

		virtual void exception(const char* data) override
		{
			defaultException(data);
		}
	};
}

#endif

#endif

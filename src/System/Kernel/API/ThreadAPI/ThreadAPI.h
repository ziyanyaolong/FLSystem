#ifndef FLSYSTEM_THREADAPI_H
#define FLSYSTEM_THREADAPI_H

#include "../EventAPI/EventAPI.h"
#include "../../IPC/IPC.h"
#include "../../IPC/Lock/FLReadWriteLock/FLReadWriteLock.h"

namespace FLSYSTEM
{
	class ThreadAPI : public EventAPI
	{
	private:
		struct ThreadData
		{
			bool isStart = false;
			bool isEnd = false;
			bool isExit = false;
			unsigned long long shallowSleepTime = 0;
		};

		FLSYSTEM_TRANSPLANTATION_TYPE::ThreadConfig _threadConfig_;

		ThreadData _threadData_;
		FLReadWriteLock _lock;

	protected:
		virtual void run() = 0;

		virtual void runInEventLoop() {}
		virtual void exitOut();
		virtual void process() override;

		void exec();
		void sleep(int64_t time);
		static bool sleep(ThreadAPI* threadPointer,int64_t time);
		void shallowSleep(int64_t time);

		FLInline FLReadWriteLock& getLock() { return _lock; }
		FLInline FLSYSTEM_TRANSPLANTATION_TYPE::ThreadConfig* getConfig() { return &_threadConfig_; }
		
	public:
		enum class ThreadState
		{
			Delete,
			Stop,
			Run,
			Ready
		};

		friend class ProcessSchedule;

		explicit ThreadAPI(FLObject* parent = nullptr, const std::string& name = std::string(""));
		virtual ~ThreadAPI() {}

		int exit();
		void start();
		bool isExit();
		bool isStart();

		void setRunTimeDelay(unsigned long long time);
		void setPriority(unsigned long priority);
		void setStackDepth(unsigned long stackDepth);
	};
}

#endif
#ifndef FLSYSTEM_THREADINTERFACE_H
#define FLSYSTEM_THREADINTERFACE_H

#include "../../../FLDefine.h"

namespace FLSYSTEM
{
	template <typename _TI>
	FLInterface ThreadInterface
	{
	private:
		_TI* getTI()
		{
			return static_cast<_TI*>(this);
		}

	protected:
		explicit ThreadInterface<_TI>() {}

	public:
		virtual ~ThreadInterface<_TI>() {}

		inline void threadDelay(unsigned long long time)
		{
			this->getTI()->fl_threadDelay(time);
		}

		inline long createThread(void* data)
		{
			return this->getTI()->fl_createThread(data);
		}

		inline void exitThread(void* pointer)
		{
			this->getTI()->fl_exitThread(pointer);
		}

	};
}

#endif

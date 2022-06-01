#ifndef FLSYSTEM_STANDARDAPI_H
#define FLSYSTEM_STANDARDAPI_H

#include "../TransplantationInterface/TransplantationInterface.h"
#include "../Transplantation.h"

namespace FLSYSTEM
{
	template<typename _TI>
	class StandardAPI : public TransplantationInterface<_TI>
	{
	public:
		explicit StandardAPI<_TI>() : TransplantationInterface<_TI>() {}
		virtual ~StandardAPI<_TI>() {}

		struct DefaultConfig
		{
			const unsigned long long maxDelay = UINT64_MAX;
		};

		struct ThreadConfig
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
			void* userData = nullptr;
		};

		typedef unsigned short FLEventSizeType;

		inline void fl_exception(const char* data)
		{
			throw data;
		}

		inline static _TI* instance()
		{
			return new _TI();
		}
	};
}

#endif

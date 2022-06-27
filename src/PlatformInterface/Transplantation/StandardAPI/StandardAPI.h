#ifndef FLSYSTEM_STANDARDAPI_H
#define FLSYSTEM_STANDARDAPI_H

#include "../../FLTRSwitch.h"
#include "../TransplantationInterface/TransplantationInterface.h"
#include "../Transplantation.h"

#define FLSYSTEM_FLVECTOR_TYPE_DEFINE std::vector
#define FLSYSTEM_FLLIST_TYPE_DEFINE std::list
#define FLSYSTEM_FLQUEUE_TYPE_DEFINE std::queue
#define FLSYSTEM_FLMAP_TYPE_DEFINE std::map

namespace FLSYSTEM
{
	template<typename _TI>
	FLInterface StandardAPI : public TransplantationInterface<_TI>
	{
	public:
		explicit StandardAPI<_TI>() : TransplantationInterface<_TI>() {}
		virtual ~StandardAPI<_TI>() {}

		struct DefaultConfig
		{
			static const unsigned long long maxDelay = INT64_MAX;
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
			unsigned long long runTimeDelay = 5;
			long returned = 0;
			void* threadClass = nullptr;
			void* userData = nullptr;
		};

		typedef unsigned short FLEventSizeType;

		inline void fl_exception(const char* data)
		{
			this->debug(data, nullptr);
#if (FLSYSTEM_EXCEPTION_MODE == 0)
#if defined(FLSYSTEM_MCU_PLATFORM)
#if defined(FLSYSTEM_ARDUINO_BOARD)
			abort();
#elif defined(FLSYSTEM_ESPRESSIF_BOARD)
			throw data;
#elif defined(FLSYSTEM_STM32_BOARD)
			abort();
#else
			abort();
#endif
#elif defined(FLSYSTEM_NORMAL_PLATFORM)
			throw data;
#endif

#elif (FLSYSTEM_EXCEPTION_MODE == 1)
			abort()
#elif (FLSYSTEM_EXCEPTION_MODE == 2)
			throw data;
#endif
			
		}

		inline static _TI* instance()
		{
			return new _TI();
		}
	};
}

#endif

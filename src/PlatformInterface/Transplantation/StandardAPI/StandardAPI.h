#ifndef FLSYSTEM_STANDARDAPI_H
#define FLSYSTEM_STANDARDAPI_H

#include "../../FLTRSwitch.h"
#include "../TransplantationInterface/TransplantationInterface.h"
#include "../Transplantation.h"

#ifdef FLSYSTEM_MEMORY_MANAGEMENT_LIB_PATH
#include FLSYSTEM_MEMORY_MANAGEMENT_LIB_PATH
#else
#if (FLSYSTEM_MEMORY_MANAGEMENT_LIB == 0)
#define FLSYSTEM_3RD_MALLOC
#elif (FLSYSTEM_MEMORY_MANAGEMENT_LIB == 1)
#define FLSYSTEM_3RD_LVGL
#elif (FLSYSTEM_MEMORY_MANAGEMENT_LIB == 2)
#define FLSYSTEM_3RD_TLSF
#endif
#include "../../3rdInclude.h"
#endif

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
			unsigned long stackDepth = 1024;
			void* parameters = nullptr;
			unsigned long priority = 1;
			void** pxCreatedTask = nullptr;
			short coreID = 0;
			unsigned long long runTimeDelay = 50;
			long returned = 0;
			void* threadClass = nullptr;
			void* userData = nullptr;
		};

		struct ThreadDelayConfig
		{
			typename _TI::ThreadConfig* threadConfig = nullptr;
			long long time = _TI::DefaultConfig::maxDelay;
		};

		typedef unsigned short FLEventSizeType;

#if (FLSYSTEM_MEMORY_MANAGEMENT_LIB == 0)
	protected:
		unsigned long long memorySize = 0;

		typedef struct fl_memory_header_t {
			std::size_t size = 0;
			std::size_t magic = 0;
		}fl_memory_header_t;

	public:
		FLInline void* fl_memory_malloc(unsigned long long size)
		{
			memorySize += size;
			memorySize += sizeof(fl_memory_header_t);
#ifdef FLSYSTEM_DEBUG_OPEN
			auto memoryPointer = malloc(size);
			if (memoryPointer == nullptr)
			{
				this->fl_exception("Unable to allocate memory");
			}
			return memoryPointer;
#else
			return malloc(size);
#endif
		}

		FLInline void fl_memory_free(void* pointer)
		{
			fl_memory_header_t* hptr = (fl_memory_header_t*)(std::size_t(pointer) - sizeof(fl_memory_header_t));
			memorySize -= hptr->size;
			memorySize -= sizeof(fl_memory_header_t);
			free(pointer);
		}

		FLInline bool fl_memory_init()
		{
			memorySize += sizeof(*this);
			return true;
		}

		FLInline unsigned long long fl_memory_getSize()
		{
			return memorySize;
		}
#elif (FLSYSTEM_MEMORY_MANAGEMENT_LIB == 1)
		FLInline void* fl_memory_malloc(unsigned long long size)
		{
			return lv_mem_alloc(size);
		}

		FLInline void fl_memory_free(void* pointer)
		{
			lv_mem_free(pointer);
		}

		FLInline bool fl_memory_init()
		{
			lv_init();
			return true;
		}

		FLInline unsigned long long fl_memory_getSize()
		{
			return lv_tlsf_size();
		}
#elif (FLSYSTEM_MEMORY_MANAGEMENT_LIB == 2)
	private:
		tlsf_t tlsf_pointer = nullptr;
		uint64_t memoryPool[FLSYSTEM_MEMORY_MANAGEMENT_SIZE / sizeof(uint64_t)]{ 0 };

	public:
		FLInline void* fl_memory_malloc(unsigned long long size)
		{
#ifdef FLSYSTEM_DEBUG_OPEN
			auto tempPointer = tlsf_malloc(tlsf_pointer, size);
			if (tempPointer == nullptr)
			{
				this->fl_exception("Unable to allocate memory");
			}
			return tempPointer;
#else
			return tlsf_malloc(tlsf_pointer, size);
#endif
		}

		FLInline void fl_memory_free(void* pointer)
		{
			tlsf_free(tlsf_pointer, pointer);
		}

		FLInline bool fl_memory_init()
		{
			tlsf_pointer = tlsf_create_with_pool(memoryPool, FLSYSTEM_MEMORY_MANAGEMENT_SIZE);
#ifdef FLSYSTEM_DEBUG_OPEN
			if (tlsf_pointer == nullptr)
			{
				this->fl_exception("Unable to initialize memory");
			}
#endif
			return (bool)tlsf_pointer;
		}

		FLInline unsigned long long fl_memory_getSize()
		{
			return tlsf_size();
		}
#else
#error Invalid Memory Management Lib
#endif
		FLInline void fl_exception(const char* data)
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
			throw data;
#elif (FLSYSTEM_EXCEPTION_MODE == 2)
			abort();
#elif (FLSYSTEM_EXCEPTION_MODE == 3)
#else
#endif
		}

		FLInline FLStaticVirtual _TI* instance()
		{
			return new _TI();
		}

	};
}

#endif

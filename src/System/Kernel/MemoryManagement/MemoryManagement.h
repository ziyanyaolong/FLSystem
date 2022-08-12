#ifndef FLSYSTEM_MEMORYMANAGEMENT_H
#define FLSYSTEM_MEMORYMANAGEMENT_H

#include "../../../PlatformInterface/PlatformInterface.h"
#include "../API/KernelAPI/KernelAPI.h"

namespace FLSYSTEM
{
	class GC_API;
	class MemoryManagement : public KernelAPI<MemoryManagement>
	{
	public:
		explicit MemoryManagement()
		{
		}
		virtual ~MemoryManagement()
		{
		}

		virtual void init() override 
		{
		}
		virtual void run() override 
		{
		}

		virtual bool load() override
		{
			return true;
		}

		static void addGC(GC_API* api)
		{
			//MemoryManagement::instance()->gc_list.push_back(api);
		}

		static void* newData(std::size_t size)
		{
			return FLSYSTEM_TRANSPLANTATION_INSTANCE->memory_malloc(size);
		}

		static void deleteData(void* ptr)
		{
			FLSYSTEM_TRANSPLANTATION_INSTANCE->memory_free(ptr);
		}

		static std::size_t getSize()
		{
			return FLSYSTEM_TRANSPLANTATION_INSTANCE->memory_getSize();
		}

		void* operator new(size_t size)
		{
			FLSYSTEM_TRANSPLANTATION_INSTANCE->memory_init();
			return FLSYSTEM_TRANSPLANTATION_INSTANCE->memory_malloc(size);
		}

		void operator delete(void* ptr)
		{
			FLSYSTEM_TRANSPLANTATION_INSTANCE->memory_free(ptr);
		}
	};
}

#endif

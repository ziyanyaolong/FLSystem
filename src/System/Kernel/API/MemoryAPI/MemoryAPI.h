#ifndef FLSYSTEM_MEMORYAPI_H
#define FLSYSTEM_MEMORYAPI_H

#include "../../MemoryManagement/MemoryManagement.h"

namespace FLSYSTEM
{
	class MemoryAPI
	{
	public:
		explicit MemoryAPI() {}
		virtual ~MemoryAPI() {}

		void* operator new(size_t size)
		{
			return MemoryManagement::newData(size);
		}

		void operator delete(void* ptr)
		{
			MemoryManagement::deleteData(ptr);
		}

	};
}

#endif

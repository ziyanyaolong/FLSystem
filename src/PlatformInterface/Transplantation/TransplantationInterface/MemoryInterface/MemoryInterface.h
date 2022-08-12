#ifndef FLSYSTEM_MEMORYINTERFACE_H
#define FLSYSTEM_MEMORYINTERFACE_H

#include "../../../FLDefine.h"
#include <iostream>
namespace FLSYSTEM
{
	template <typename _TI>
	FLInterface MemoryInterface
	{
	private:
		_TI* getTI()
		{
			return static_cast<_TI*>(this);
		}

	protected:
		explicit MemoryInterface<_TI>() {}

	public:
		virtual ~MemoryInterface<_TI>() {}

		inline void* memory_malloc(unsigned long long size)
		{
			return this->getTI()->fl_memory_malloc(size);
		}

		inline void memory_free(void* pointer)
		{
			this->getTI()->fl_memory_free(pointer);
		}

		inline bool memory_init()
		{
			return this->getTI()->fl_memory_init();
		}

		inline unsigned long long memory_getSize()
		{
			return this->getTI()->fl_memory_getSize();
		}
	};
}

#endif

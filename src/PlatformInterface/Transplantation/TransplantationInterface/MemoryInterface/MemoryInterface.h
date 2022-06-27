#ifndef FLSYSTEM_MEMORYINTERFACE_H
#define FLSYSTEM_MEMORYINTERFACE_H

#include "../../../FLDefine.h"

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

	};
}

#endif

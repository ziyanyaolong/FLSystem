#ifndef FLSYSMTE_TRANSPLANTATIONINTERFACE_H
#define FLSYSMTE_TRANSPLANTATIONINTERFACE_H

#include "../../FLTRSwitch.h"

#include "DebugInterface/DebugInterface.h"
#include "ExceptionInterface/ExceptionInterface.h"
#include "MemoryInterface/MemoryInterface.h"
#include "ThreadInterface/ThreadInterface.h"
#include "ThreadLockInterface/ThreadLockInterface.h"

namespace FLSYSTEM
{
	template <typename _TI>
	FLInterface TransplantationInterface
		: public DebugInterface<_TI>,
		public ExceptionInterface<_TI>,
		public MemoryInterface<_TI>,
		public ThreadInterface<_TI>,
		public ThreadLockInterface<_TI>
	{
	protected:
		explicit TransplantationInterface<_TI>()
			: DebugInterface<_TI>(),
			ExceptionInterface<_TI>(),
			MemoryInterface<_TI>(),
			ThreadInterface<_TI>(),
			ThreadLockInterface<_TI>()
		{}

	public:
		virtual ~TransplantationInterface<_TI>() {};
	};
}
#endif

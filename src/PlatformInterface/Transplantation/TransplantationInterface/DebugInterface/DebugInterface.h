#ifndef FLSYSTEM_DEBUGINTERFACE_H
#define FLSYSTEM_DEBUGINTERFACE_H

#include "../../../FLDefine.h"
#include "../../../../FLSystemConfig.h"

namespace FLSYSTEM
{
	template <typename _TI>
	FLInterface DebugInterface
	{
	private:
		_TI* getTI()
		{
			return static_cast<_TI*>(this);
		}

	protected:
		explicit DebugInterface<_TI>() {}

	public:
		virtual ~DebugInterface<_TI>() {}

		inline void debug(const char* str, void* data = nullptr)
		{
#ifdef FLSYSTEM_DEBUG_OPEN
			this->getTI()->fl_debug(str, data);
#endif
		}


	};
}

#endif

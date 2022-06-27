#ifndef FLSYSTEM_EXCEPTIONINTERFACE_H
#define FLSYSTEM_EXCEPTIONINTERFACE_H

#include "../../../FLDefine.h"

namespace FLSYSTEM
{
	template <typename _TI>
	FLInterface ExceptionInterface
	{
	private:
		_TI* getTI()
		{
			return static_cast<_TI*>(this);
		}

	protected:
		explicit ExceptionInterface<_TI>() {}

	public:
		virtual ~ExceptionInterface<_TI>() {}

		inline void exception(const char* data)
		{
			this->getTI()->fl_exception(data);
		}
	};
}

#endif

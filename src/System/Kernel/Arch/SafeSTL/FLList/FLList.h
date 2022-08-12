#ifndef FLSYSTEM_FLLIST_H
#define FLSYSTEM_FLLIST_H

#define FLSYSTEM_3RD_TLSL

#include "../STL_Bass/STL_Basic.h"
#include "../../../KernelInclude.h"

namespace FLSYSTEM
{
	template<typename T>
	class FLList : public STL_Basic
	{
	public:
		FLSYSTEM_FLLIST_TYPE<T> list;
		explicit FLList(FLList::Mode mode = FLList::Mode::HaveLock) : STL_Basic(mode) {}
	};
}

#endif
#ifndef FLSYSTEM_FLLIST_H
#define FLSYSTEM_FLLIST_H

#define FLSYSTEM_3RD_LIST

#include "../STL_Bass/STL_Basic.h"
#include "../../../KernelInclude.h"

namespace FLSYSTEM
{
	template<typename T>
	class FLList
	{
	public:
		FLSYSTEM_FLLIST_TYPE<T> list;
	};
}

#endif
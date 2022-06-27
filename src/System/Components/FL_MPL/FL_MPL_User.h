#ifndef FLSYSTEM_FL_MPL_USER_H
#define FLSYSTEM_FL_MPL_USER_H

#include "FL_MPL_BaseType.h"
#include "FL_MPL_Logic.h"

namespace FLSYSTEM
{
	namespace FL_MPL_USER
	{
		using namespace FL_MPL_BaseType;
		using namespace FL_MPL_Logic;
		namespace FL_MPL_Registry
		{
			template<typename _T1>
			struct RegistryModeType1
			{
				using tag = FLVector<_T1>;
			};

			template<typename _T1, typename _T2>
			struct RegistryModeType2
			{
				using tag = FLMap<_T1, _T2>;
			};

			template<typename _T1, typename _T2 = fl_null>
			struct RegistryModeSet
			{
				using type = fl_if_else<fl_is_same<_T2, fl_null>, RegistryModeType1<_T1>, RegistryModeType2<_T1, _T2> >;
				using tag = typename type::tag;
			};
		}
	}
}

#endif

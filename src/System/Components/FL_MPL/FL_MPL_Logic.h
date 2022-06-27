#ifndef FLSYSTEM_FL_MPL_LOGIC_H
#define FLSYSTEM_FL_MPL_LOGIC_H

#include "FL_MPL_BaseType.h"

namespace FLSYSTEM
{
	namespace FL_MPL_Logic
	{
		using namespace FL_MPL_BaseType;
		template <typename Flag, typename True, typename False>
		struct fl_if_else_impl : public True {};

		template <typename True, typename False>
		struct fl_if_else_impl<fl_boolean<false>, True, False> : public False {};

		template <typename Flag, typename True, typename False>
		struct fl_if_else : public fl_if_else_impl<typename Flag::type, True, False> {};

		template <typename, typename>
		struct fl_is_same : public fl_boolean<false> {};

		template <typename _Tp>
		struct fl_is_same<_Tp, _Tp> : public fl_boolean<true> {};
	}
}

#endif

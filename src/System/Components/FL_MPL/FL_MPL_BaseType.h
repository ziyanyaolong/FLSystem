#ifndef FLSYSTEM_FL_MPL_BASETYPE_H
#define FLSYSTEM_FL_MPL_BASETYPE_H

namespace FLSYSTEM
{
	namespace FL_MPL_BaseType
	{
		template <typename _Ty, _Ty _Val>
		struct fl_integral_constant {
			static constexpr _Ty value = _Val;

			using value_type = _Ty;
			using type = fl_integral_constant;

			constexpr operator value_type() const noexcept {
				return value;
			}

			constexpr value_type operator()() const noexcept {
				return value;
			}
		};

		struct fl_null {};

		template <bool flag>
		struct fl_boolean : public fl_integral_constant<bool, flag> {};

		template <bool flag>
		struct fl_int : public fl_integral_constant<int, flag> {};

		template <bool flag>
		struct fl_short : public fl_integral_constant<short, flag> {};
	}

	
}

#endif

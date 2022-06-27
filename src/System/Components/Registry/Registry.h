#ifndef FLSYSTEM_REGISTRY_H
#define FLSYSTEM_REGISTRY_H

#include "../../Kernel/Arch/Object/FLObject.h"
#include "../../Kernel/Arch/SafeSTL/FLMap/FLMap.h"

#include "../FL_MPL/FL_MPL_User.h"

namespace FLSYSTEM
{

	template<typename _T1, typename _T2 = FL_MPL_BaseType::fl_null>
	class Registry
	{
	private:
		typename FL_MPL_USER::FL_MPL_Registry::RegistryModeSet<_T1, _T2>::tag table;

	public:
		Registry() {}
		virtual ~Registry() {}

		void reg(_T1 key) { table.push_back(key); }
		void reg(_T1 key, _T2 value) { table[key] = value; }
		typename FL_MPL_USER::FL_MPL_Registry::RegistryModeSet<_T1, _T2>::tag& getTable() { return table; }

	protected:



	};
}

#endif
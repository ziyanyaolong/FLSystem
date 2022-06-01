#ifndef FLSYSTEM_REGISTRY_H
#define FLSYSTEM_REGISTRY_H

#include <string>
#include <map>

#include "../../System/Object/FLObject.h"

namespace FLSYSTEM
{
	class Registry
	{
	private:

	public:
		Registry() {}
		virtual ~Registry() {}

		void reg(const FLObject* key, const FLObject* value) {}

	protected:



	};
}

#endif
#ifndef FLSYSTEM_TRANSPLANTATION_H
#define FLSYSTEM_TRANSPLANTATION_H

#include "TransplantationInterface/TransplantationInterface.h"

namespace FLSYSTEM
{
	template <typename TI>
	class Transplantation
	{
	private:
		static TransplantationInterface<TI>* transplantationClass;

	protected:
		explicit Transplantation<TI>() {}

	public:
		virtual ~Transplantation<TI>() {}

		inline static TransplantationInterface<TI>* instance()
		{
			if (transplantationClass == nullptr)
				transplantationClass = static_cast<TransplantationInterface<TI>*>(TI::instance());

			return transplantationClass;
		};
	};
}

#endif

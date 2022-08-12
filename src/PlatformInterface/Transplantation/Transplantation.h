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
		explicit Transplantation<TI>() { }

	public:
		virtual ~Transplantation<TI>() {}

		FLInline FLStatic TransplantationInterface<TI>* instance()
		{
			if (transplantationClass == nullptr)
				transplantationClass = static_cast<TransplantationInterface<TI>*>(TI::instance());

			return transplantationClass;
		};

		FLInline FLStatic unsigned long long getSize()
		{
			std::cout << sizeof(*(Transplantation<TI>::transplantationClass))  << std::endl;
			return sizeof(*(Transplantation<TI>::transplantationClass));
		}
	};
}

#endif

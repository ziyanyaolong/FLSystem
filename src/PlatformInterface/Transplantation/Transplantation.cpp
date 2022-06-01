#include "Transplantation.h"
#include "../PlatformInterface.h"

template class FLSYSTEM::Transplantation<FLSYSTEM_TRANSPLANTATION_TYPE>;
template <typename TI> FLSYSTEM::TransplantationInterface<TI>* FLSYSTEM::Transplantation<TI>::transplantationClass = nullptr;
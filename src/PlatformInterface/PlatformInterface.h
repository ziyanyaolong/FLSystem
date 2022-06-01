#ifndef FLSYSTEM_PLATFORMINTERFACE_H
#define FLSYSTEM_PLATFORMINTERFACE_H

#include "FLTRSwitch.h"

#ifdef FLSYSTEM_ENABLE_LVGL_8
#define FLSYSTEM_3RD_LVGL
#endif

#include "3rdInclude.h"

#ifndef FLSYSTEM_ESPRESSIF_BOARD
#define FLSYSTEM_TASK_START_SCHEDULER
#endif

#if defined(FLSYSTEM_ENABLE_DEFAULT_LIBRARY)
#include "Transplantation/DefaultLibrary/DefaultLibrary.h"
#define FLSYSTEM_TRANSPLANTATION_TYPE FLSYSTEM::DefaultLibrary
#elif defined(FLSYSTEM_ENABLE_FREERTOS_LIBRARY)
#include "Transplantation/FreeRTOSLibrary/FreeRTOSLibrary.h"
#define FLSYSTEM_TRANSPLANTATION_TYPE FLSYSTEM::FreeRTOSLibrary
#elif defined(FLSYSTEM_ENABLE_CUSTOM_TRANSPLANTATION)
#define FLSYSTEM_TRANSPLANTATION_TYPE FLSYSTEM_SET_CUSTOM_TRANSPLANTATION
#else
#error No Transplantation!
#endif

#include "Transplantation/Transplantation.h"

#define FLSYSTEM_TRANSPLANTATION_INSTANCE (FLSYSTEM::Transplantation<FLSYSTEM_TRANSPLANTATION_TYPE>::instance())

#endif

#include "3rdInclude.h"
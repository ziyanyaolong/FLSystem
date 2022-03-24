#ifndef FLSYSTEM_PLATFORMINTERFACE_H
#define FLSYSTEM_PLATFORMINTERFACE_H

#include "../FLSystemConfig.h"

//框架配置部分
#ifdef FLSYSTEM_ENABLE_ARDUINO
#define FLSYSTEM_3RD_ARDUINO
#else
#define FLSYSTEM_3RD_STDINT
#endif

//线程库配置部分
#if (FLSYSTEM_ENABLE_THREADLIB == 0)
#define FLSYSTEM_3RD_THREAD
#elif (FLSYSTEM_ENABLE_THREADLIB == 1)
#define FLSYSTEM_3RD_FREERTOS
#else
#error "No Thread Lib Include!"
#endif

#ifdef FLSYSTEM_ENABLE_LVGL_8
#define FLSYSTEM_3RD_LVGL
#endif

#if (!defined(FLSYSTEM_ENABLE_TFT_ESPI) && !defined(FLSYSTEM_ENABLE_U8G2))
#define FLSYSTEM_ENABLE_CUSTOM_DISPLAY
#endif

#ifdef FLSYSTEM_ENABLE_DEVELOPMENT_BOARD_INSPECTION_AUTO
//自动检测部分（无需手动配置）
#if (defined(__AVR_ATmega328P__) || defined(__AVR_ATmega32U4__) || \
	 defined(TEENSYDUINO) || defined(__AVR_ATmega2560__) ||        \
	 defined(__AVR_ATmega4809__)) &&                               \
	!defined(__IMXRT1062__)
#define FLSYSTEM_ARDUINO_BOARD
#elif defined(ARDUINO_STM32_FEATHER)
#define FLSYSTEM_STM32_BOARD
#elif defined(NRF52_SERIES) || defined(ESP32) || defined(ESP8266) || \
	defined(ARDUINO_ARCH_STM32) || defined(__IMXRT1062__)
#define FLSYSTEM_ESPRESSIF_BOARD
#else
#define FLSYSTEM_UNKNOW_BOARD
#endif
#endif

#include "3rdInclude.h"

#ifndef FLSYSTEM_ESPRESSIF_BOARD
#define FLSYSTEM_TASK_START_SCHEDULER
#endif

#ifdef FLSYSTEM_3RD_THREAD

#if !_HAS_CXX20
#error("You must use C++20 or above")
#endif

#ifndef FLSYSTEM_UNKNOW_BOARD
#error You may not use this thread library in microcontrollers
#endif

#endif

#include "FLSystemTypeConfig.h"

namespace FLSYSTEM
{
	FLTaskReturnedType FLNewThread(
		FLTaskFunctionType pxTaskCode,
		FLTaskNameType pcName,
		FLTaskStackDepthType usStackDepth,
		FLTaskParametersType pvParameters,
		FLTaskPriorityType uxPriority,
		FLTaskHandleType* pxCreatedTask,
		FLTaskCoreID xCoreID);

	void FLExitTask(FLTaskHandleType data = nullptr);

	void FLTaskDelay(long long time);

	void FLException(const char* data);
}

#endif

#include "3rdInclude.h"
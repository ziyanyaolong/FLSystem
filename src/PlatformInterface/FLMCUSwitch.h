#include "../FLSystemConfig.h"

//框架配置部分
#ifdef FLSYSTEM_ENABLE_ARDUINO
#define FLSYSTEM_3RD_ARDUINO
#else
#define FLSYSTEM_3RD_STDINT
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
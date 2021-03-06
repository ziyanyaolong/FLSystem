#ifndef FLSYSTEM_FLSYSTEMCONFIG_H
#define FLSYSTEM_FLSYSTEMCONFIG_H
//在这里你可以管理FL系统的设置

//开发板设置
// #define FLSYSTEM_ESPRESSIF_BOARD
// #define FLSYSTEM_STM32_BOARD
// #define FLSYSTEM_ARDUINO_BOARD
// #define FLSYSTEM_UNKNOW_BOARD
#define FLSYSTEM_ENABLE_DEVELOPMENT_BOARD_INSPECTION_AUTO   //启用开发板自动检测（默认设置）

//#define FLSYSTEM_ENABLE_ARDUINO     //启用Arduino库

#define FLSYSTEM_ENABLE_THREADLIB	0	//启用线程库 (0:自动/自定义(默认选项), 1:强制使用C++标准线程库, 2:强制使用FreeRTOS库)

// FreeRTOS配置部分
//#define FLSYSTEM_ENABLE_MAIN_THREAD // 启用后可以选择是否保留主线程不退出，注意，只有线程库允许可以继续循环的情况下才有作用
//#define FLSYSTEM_ENABLE_FINE_DISTRIBUTION //开启后可以设置线程具体加载在哪个线程

#define FLSYSTEM_EXCEPTION_MODE 0 // 异常模式设置(0:自动/自定义(默认选项), 1:强制使用throw, 2:强制使用abort)

//#define FLSYSTEM_DEBUG_OPEN	//开启调试模式

#define FLSYSTEM_ENABLE_LVGL

#endif

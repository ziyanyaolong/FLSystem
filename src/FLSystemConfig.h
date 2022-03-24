#ifndef FLSYSTEM_FLSYSTEMCONFIG_H
#define FLSYSTEM_FLSYSTEMCONFIG_H
//在这里你可以管理FL系统的设置

//开发板设置
// #define FLSYSTEM_ESPRESSIF_BOARD
// #define FLSYSTEM_STM32_BOARD
// #define FLSYSTEM_ARDUINO_BOARD
// #define FLSYSTEM_UNKNOW_BOARD
#define FLSYSTEM_ENABLE_DEVELOPMENT_BOARD_INSPECTION_AUTO   //启用开发板自动检测（默认设置）

//文件系统底层使用
// #define FLSYSTEM_ENABLE_FATFS
// #define FLSYSTEM_ENABLE_ARDUINO_SD
// #define FLSYSTEM_ENABLE_CUSTOM

// #define FLSYSTEM_ENABLE_ARDUINO     //启用Arduino库

#define FLSYSTEM_ENABLE_THREADLIB	1       //启用线程库 ( 0:C++标准线程库, 1：FreeRTOS库 )
// #define FLSYSTEM_ENABLE_LVGL_8              //启用LVGL 8
// #define FLSYSTEM_ENABLE_LVGL_TICK_SYNCH	//启用LVGL的Tick同步函数

// FreeRTOS配置部分
//#define FLSYSTEM_ENABLE_MAIN_THREAD // 启用后可以选择是否保留主线程不退出，注意，只有线程库允许可以继续循环的情况下才有作用
// #define FLSYSTEM_ENABLE_FINE_DISTRIBUTION //开启后可以设置线程具体加载在哪个线程

// LVGL配置部分
// #define FLSYSTEM_ENABLE_FLSYSTEM_DEFAULT_SYSTEM //启用FLSystem自带的LVGL移植，如文件系统，显示系统等
// #define FLSYSTEM_ENABLE_LVGL_FILE_SYSTEM //启用LVGL的文件系统
// #define FLSYSTEM_ENABLE_LVGL_MEMORY_MANAGE //启用LVGL自己的内存管理


#define FLSYSTEM_EXCEPTION_MODE 2 // 异常模式设置(0:使用throw, 1:使用abort, 2:自动)
#endif

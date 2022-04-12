#ifdef FLSYSTEM_3RD_STDINT
#include <stdint.h>
#endif

#ifdef FLSYSTEM_3RD_STRING
#include<string>
#endif

#ifdef FLSYSTEM_3RD_THREAD
#include <thread>
#endif

#ifdef FLSYSTEM_3RD_ALGORITHM
#include <algorithm>
#endif

#ifdef FLSYSTEM_3RD_VECTOR
#include <vector>
#endif

#ifdef FLSYSTEM_3RD_QUEUE
#include <queue>
#endif

#ifdef FLSYSTEM_3RD_LIST
#include <list>
#endif

#ifdef FLSYSTEM_3RD_MAP
#include <map>
#endif

#ifdef FLSYSTEM_3RD_ATOMIC

#ifndef FLSYSTEM_ARDUINO_BOARD
#include <atomic>
#else 

#endif

#endif

#ifdef FLSYSTEM_3RD_ARDUINO
#include <Arduino.h>
#endif

#ifdef FLSYSTEM_3RD_LVGL
#if _MSC_VER > 0
#include <lvgl/lvgl.h>
#else
#include <lvgl.h>
#endif
#endif

#ifdef FLSYSTEM_3RD_FREERTOS

#ifdef FLSYSTEM_ARDUINO_BOARD
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#else
#include <FreeRTOS.h>

#if _MSC_VER > 0
#include "task.h"
#include <Windows.h>
#include "queue.h"
#include "semphr.h"
#include "resource.h"
#endif

#endif

#endif
#ifdef FLSYSTEM_3RD_STDINT
#include <stdint.h>
#endif

#ifdef FLSYSTEM_3RD_IOSTREAM
#include <iostream>
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

#ifdef FLSYSTEM_3RD_STDIO
#include <stdio.h>
#endif

#ifdef FLSYSTEM_3RD_MUTEX
#include <mutex>
#endif

#ifdef FLSYSTEM_3RD_CONDITION_VARIABLE
#include <condition_variable>
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
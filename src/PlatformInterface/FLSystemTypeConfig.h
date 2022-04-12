//#ifndef FLSYSTEM_FLSYSTEM_TYPE_CONFIG_H
//#define FLSYSTEM_FLSYSTEM_TYPE_CONFIG_H
//
//#include "3rdInclude.h"
//
//namespace FLSYSTEM
//{
//#ifndef FLSYSTEM_3RD_FREERTOS
//	typedef unsigned long long FLRunTimeDelayType;
//	typedef void (*_TaskFun_)(void*);
//	typedef _TaskFun_ FLTaskFunctionType;
//	typedef const char* const FLTaskNameType;
//	typedef unsigned short FLTaskStackDepthType;
//	typedef void* FLTaskParametersType;
//	typedef unsigned long FLTaskPriorityType;
//	typedef void* FLTaskHandleType;
//	typedef	long FLTaskReturnedType;
//	typedef short FLTaskCoreID;
//
//#else
//	typedef unsigned long long FLRunTimeDelayType;
//	typedef TaskFunction_t FLTaskFunctionType;
//	typedef const char* const FLTaskNameType;
//	typedef unsigned short FLTaskStackDepthType;
//	typedef void* FLTaskParametersType;
//	typedef UBaseType_t FLTaskPriorityType;
//	typedef TaskHandle_t FLTaskHandleType;
//	typedef	BaseType_t FLTaskReturnedType;
//	typedef short FLTaskCoreID;
//
//#endif
//
//	
//}
//
//#endif 
#include "FLThread.h"

//FLSYSTEM::FLThread::FLThread(FLObject* parent) : ThreadAPI(parent)
//{
//}
//
//FLSYSTEM::FLThread::~FLThread()
//{
//	exit();
//}
//
//bool FLSYSTEM::FLThread::wait(int64_t time)
//{
//	return true;
//}
//
//void FLSYSTEM::FLThread::quit()
//{
//	exit();
//}
//
//void FLSYSTEM::FLThread::start()
//{
//	if (isStart)
//		return;
//
//	isStart = true;
//	Kernel::processSchedule.createThread(this);
//}
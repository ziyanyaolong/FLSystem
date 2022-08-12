#include "kernel.h"

FLSYSTEM::Kernel::Kernel() : KernelAPI(), GC_API()
{
}

FLSYSTEM::Kernel::~Kernel()
{
	if (kernelRun)
	{
		kernelRun->deleteLater();
	}

	unloadKernel();
}

void FLSYSTEM::Kernel::init()
{
	MemoryManagement::instance()->init();
	ProcessSchedule::instance()->init();
	IPC::instance()->init();
}

void FLSYSTEM::Kernel::run()
{
	MemoryManagement::instance()->run();
	ProcessSchedule::instance()->run();
	IPC::instance()->run();
	//std::cout << MemoryManagement::getSize() << std::endl;
}

void FLSYSTEM::Kernel::loadKernel()
{
	MemoryManagement::instance()->load();
	IPC::instance()->load();
	ProcessSchedule::instance()->load();
}

void FLSYSTEM::Kernel::unloadKernel()
{
	MemoryManagement::instance()->unload();
	IPC::instance()->unload();
	ProcessSchedule::instance()->unload();
}

bool FLSYSTEM::Kernel::load()
{
	Kernel::instance()->loadKernel();
	return true;
}

FLSYSTEM::Kernel::SysCallError FLSYSTEM::Kernel::sysCall(SysCallNumber number, void* data)
{
	if ((number != SysCallNumber::EmptyRequest) && (data == nullptr))
	{
		return SysCallError::EmptyPointer;
	}

	switch (number)
	{
	case FLSYSTEM::Kernel::SysCallNumber::EmptyRequest:
		return SysCallError::NoError;
		break;
	case FLSYSTEM::Kernel::SysCallNumber::ThreadCreateRequest:
		if (ProcessSchedule::instance()->createThread(static_cast<ThreadAPI*>(data)) == 0)
		{
			return SysCallError::NoError;
		}
		break;
	case FLSYSTEM::Kernel::SysCallNumber::ProcessCreateRequest:
		if (ProcessSchedule::instance()->createProcess(static_cast<ProcessScheduleAPI*>(data)) == 0)
		{
			return SysCallError::NoError;
		}
		break;
	case FLSYSTEM::Kernel::SysCallNumber::ThreadDeleteRequest:
		ProcessSchedule::instance()->deleteThread(static_cast<ThreadAPI*>(data));
		return SysCallError::NoError;
		break;
	case FLSYSTEM::Kernel::SysCallNumber::ProcessDeleteRequest:
		ProcessSchedule::instance()->deleteProcess(static_cast<ProcessScheduleAPI*>(data));
		return SysCallError::NoError;
		break;
	default:
		break;
	}
	return SysCallError::UnknownError;
}
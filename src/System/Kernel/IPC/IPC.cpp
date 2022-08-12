#include "IPC.h"

FLSYSTEM::EventCore* FLSYSTEM::IPC::eventCore = nullptr;

FLSYSTEM::IPC::IPC() : KernelAPI(), GC_API()
{
}

FLSYSTEM::IPC::~IPC()
{
	if (eventCore)
	{
		delete eventCore;
		eventCore = nullptr;
	}
}

void FLSYSTEM::IPC::init()
{
	
}

void FLSYSTEM::IPC::run()
{
	eventCore->process();
}

bool FLSYSTEM::IPC::load()
{
	if (eventCore == nullptr)
	{
		eventCore = new EventCore();
	}

	return true;
}
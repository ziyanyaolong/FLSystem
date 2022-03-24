#include "kernel.h"

FLSYSTEM::ProcessSchedule FLSYSTEM::Kernel::processSchedule;
FLSYSTEM::IPC FLSYSTEM::Kernel::ipc;

FLSYSTEM::Kernel::Kernel()
{
}

FLSYSTEM::Kernel::~Kernel()
{
}

void FLSYSTEM::Kernel::init()
{
    ipc.begin();
    processSchedule.begin();
}

void FLSYSTEM::Kernel::run()
{
    ipc.run();
    processSchedule.run();
}
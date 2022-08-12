#ifndef FLSYSTEM_FLSYSTEM_MAIN_H
#define FLSYSTEM_FLSYSTEM_MAIN_H

#include "PlatformInterface/PlatformInterface.h"
#include "System/Kernel/Kernel.h"

namespace FLSYSTEM
{
	  
	class FLSystem
	{
	private:
		bool isRun = false;
	//	FLQueue<ProcessScheduleAPI*> processList;
	//	FLVector<ProcessScheduleAPI*> mergeList;

	//protected:

	public:
		virtual ~FLSystem();
		explicit FLSystem();

		void setTransplantation() {}
		void init();
		void start();
		void registerProcess(ProcessScheduleAPI* api);
		void registerThread(ThreadAPI* api);

		void* operator new(size_t size)
		{
			Kernel::boot();
			return MemoryManagement::newData(size);
		}

		void operator delete(void* ptr)
		{
			MemoryManagement::deleteData(ptr);
			Kernel::close();
		}
	};

	extern FLSystem* FL_BIOS;
}

#endif 
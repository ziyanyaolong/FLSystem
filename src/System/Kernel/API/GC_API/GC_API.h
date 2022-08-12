#ifndef FLSYSTEM_GC_API_H
#define FLSYSTEM_GC_API_H

#include "../MemoryAPI/MemoryAPI.h"

namespace FLSYSTEM
{
	class GC_API : public MemoryAPI
	{
	public:
		explicit GC_API() : MemoryAPI() {}
		virtual ~GC_API() {}

		void deleteLater() { MemoryManagement::addGC(this); }
	};
}

#endif

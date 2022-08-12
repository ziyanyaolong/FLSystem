#ifndef FLSYSTEM_KERNELAPI_H
#define FLSYSTEM_KERNELAPI_H

#include "../../KernelInclude.h"
#include "KAStaticInstance/KAStaticInstance.h"

namespace FLSYSTEM
{
	template <typename T>
	class KernelAPI : public KAStaticInstance<T>
	{
	public:
		explicit KernelAPI() {}
		virtual ~KernelAPI()
		{ 
		}

		virtual void init() = 0;
		virtual void run() = 0;
		virtual bool load() = 0;
		
		void unload()
		{
			if (this->kernel)
			{
				delete this->kernel;
				this->kernel = nullptr;
			}
		}

		virtual int kernelCall(void* data) { return -1; }
	};
}

#endif

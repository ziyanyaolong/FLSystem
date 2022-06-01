#ifndef FLSYSTEM_MEMORYMANAGEMENT_H
#define FLSYSTEM_MEMORYMANAGEMENT_H

#include "../../../PlatformInterface/PlatformInterface.h"

namespace FLSYSTEM
{
	class MemoryManagement
	{
	private:
		unsigned long long StaticMemorySize = 0;
		unsigned long long DynamicmemorySize = 0;

	public:
		explicit MemoryManagement() {}
		virtual ~MemoryManagement() {}

		template<typename T, typename ... Args>
		static T* newDynamic(Args ... args)
		{
			auto* pTemp = new T(args...);
			if (pTemp)
			{
				sizeof(T);
				return pTemp;
			}
			else
			{
				FLExt
				return nullptr;
			}
		}

		template<typename T, typename ... Args>
		static T* newStatic(Args ... args)
		{
			return new T(args...);
		}

		template<typename T>
		static bool deleteDynamic(T* pointer)
		{
			return true;
		}

		template<typename T>
		static bool deleteStatic(T* pointer)
		{
			return true;
		}

		template<typename T>
		static bool deletAuto(T* pointer)
		{
			return true;
		}

	};
}

#endif

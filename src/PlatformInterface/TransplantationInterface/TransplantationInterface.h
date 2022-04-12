#ifndef FLSYSMTE_TRANSPLANTATIONINTERFACE_H
#define FLSYSMTE_TRANSPLANTATIONINTERFACE_H

namespace FLSYSTEM
{
	class TransplantationInterface
	{
	private:
		static TransplantationInterface* transplantation;

	public:
		virtual ~TransplantationInterface() {}


		typedef unsigned short FLEventSizeType;
		typedef void* FLUserDataType;

		virtual long createTask(void* data) = 0;
		virtual void exitTask(void* pointer) = 0;
		virtual void taskDelay(long long time) = 0;
		virtual void exception(const char* data) = 0;

		template<typename T>
		static TransplantationInterface* instance()
		{
			if (transplantation == nullptr)
			{
				transplantation = new T();
			}

			return transplantation;
		}

		void defaultException(const char* data)
		{
#if (FLSYSTEM_EXCEPTION_MODE == 0)
			throw data;

#elif (FLSYSTEM_EXCEPTION_MODE == 1)
			abort();

#elif (FLSYSTEM_EXCEPTION_MODE == 2)

#ifdef FLSYSTEM_ESPRESSIF_BOARD
			abort();

#elif defined FLSYSTEM_ARDUINO_BOARD
			abort();

#elif defined FLSYSTEM_STM32_BOARD
			abort();

#elif defined FLSYSTEM_UNKNOW_BOARD
			throw data;

#endif

#else
#endif
		}

	protected:
		explicit TransplantationInterface() {}
	};
}
#endif

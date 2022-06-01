#ifndef FLSYSTEM_DEBUGINTERFACE_H
#define FLSYSTEM_DEBUGINTERFACE_H

namespace FLSYSTEM
{
	template <typename _TI>
	class DebugInterface
	{
	private:
		_TI* getTI()
		{
			return static_cast<_TI*>(this);
		}

	protected:
		explicit DebugInterface<_TI>() {}

	public:
		virtual ~DebugInterface<_TI>() {}

		inline void debugPrint(const char* str, void* data = nullptr)
		{
			this->getTI()->fl_debugPrint(str, data);
		}


	};
}

#endif

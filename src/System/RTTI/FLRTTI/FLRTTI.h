#ifndef FLSYSTEM_FLRTTI_H
#define FLSYSTEM_FLRTTI_H

#define RTTINameSet(name)	\
public:						\
enum class Type				\
{							\
	Unknown = 0x0,			\
	name = 0x1				\
};							\

namespace FLSYSTEM
{
	class FLRTTI
	{
	private:
		enum class Type;
		void* _type = nullptr;

	public:
		FLRTTI() {}
		virtual ~FLRTTI() {}

		
	};

}

#endif
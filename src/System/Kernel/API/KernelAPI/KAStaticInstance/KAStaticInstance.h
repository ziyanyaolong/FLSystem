#ifndef FLSYSTEM_KASTATICINSTANCE_H
#define FLSYSTEM_KASTATICINSTANCE_H

namespace FLSYSTEM
{
	template <typename T>
	class KAStaticInstance
	{
	protected:
		static T* kernel;

	public:
		explicit KAStaticInstance<T>() {}
		virtual ~KAStaticInstance<T>()
		{
			if (KAStaticInstance<T>::kernel)
			{
				delete kernel;
				kernel = nullptr;
			}
		}

		static T* instance()
		{
			if (kernel == nullptr)
			{
				return (kernel = new T());
			}
			else
			{
				return KAStaticInstance<T>::kernel;
			}
		}
	};

	template <typename T>
	T* FLSYSTEM::KAStaticInstance<T>::kernel = nullptr;
}

#endif

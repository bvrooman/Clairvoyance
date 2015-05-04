#ifndef CLAIRE_SINGLETON_H
#define CLAIRE_SINGLETON_H

#include "ClairePrerequisites.h"

#define CLAIRE_SINGLETON_FRIEND \
	template<class T> friend class Claire::core::Singleton;

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	template<class T>
	class Singleton
	{
		CLAIRE_NON_COPYABLE(Singleton)

	private:
		struct Deleter
		{
			void operator()(T* t)
			{
				delete t;
			}
		};

	public:
		typedef std::unique_ptr<T, Deleter> TypeUPtr;

	public:
		static T* getInstance(void)
		{
			if(mInstance.get() == nullptr)
			{
				mInstance = TypeUPtr(new T());
			}
			return mInstance.get();
		}

	protected:
		Singleton(void) {}
		virtual ~Singleton(void) {}

	protected:
		static TypeUPtr mInstance;
	};

	CLAIRE_NAMESPACE_END
}

#endif
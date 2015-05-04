#ifndef CLAIRE_THREAD_SPECIFIC_PTR_STD_H
#define CLAIRE_THREAD_SPECIFIC_PTR_STD_H

#include "ClairePrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)
	CLAIRE_NAMESPACE_BEGIN(threading_internal)
	
	template<typename T>
	class ThreadSpecificPtrSTD
	{
	private:
		typedef T* pointer;
		static CLAIRE_THREAD_LOCAL pointer mPtr;

	public:
		pointer get(void) const
		{
			return mPtr;
		}

		void reset(pointer ptr)
		{
			if (mPtr && mPtr != ptr)
			{
				delete mPtr;
			}
			mPtr = ptr;
		}

		T* operator->(void) { return get(); }
		T& operator*(void) { return *get(); }

		T* operator->(void) const { return get(); }
		T& operator*(void) const { return *get(); }
	};

	template<typename T>
	typename ThreadSpecificPtrSTD<T>::pointer ThreadSpecificPtrSTD<T>::mPtr = nullptr;

	CLAIRE_NAMESPACE_END
	CLAIRE_NAMESPACE_END
}

#endif
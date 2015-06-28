#ifndef CLAIRE_THREAD_LOCAL_PTR_STD_H
#define CLAIRE_THREAD_LOCAL_PTR_STD_H

#include "ClairePrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)
	CLAIRE_NAMESPACE_BEGIN(threading_internal)
	
	template<typename T>
	class ThreadLocalPtrSTD
	{
	private:
		typedef T* pointer;
		static thread_local pointer mPtr;

	public:
		ThreadLocalPtrSTD(void) = default;
		~ThreadLocalPtrSTD(void) = default;

		ThreadLocalPtrSTD(const pointer& ptr)
		{
			mPtr = ptr;
		}

		pointer get(void) const
		{
			return mPtr;
		}
		 
		ThreadLocalPtrSTD& operator = (pointer ptr)
		{
			reset(ptr);
			return *this;
		}

		void reset(pointer ptr)
		{
			if(mPtr && mPtr != ptr)
			{
				delete mPtr;
			}
			mPtr = ptr;
		}

		T* operator->(void) { return get(); }
		T& operator*(void) { return *get(); }

		T* operator->(void) const { return get(); }
		T& operator*(void) const { return *get(); }

		operator T*(void) { return get(); }
		operator T*(void) const { return get(); }
	};

	template<typename T>
	typename thread_local ThreadLocalPtrSTD<T>::pointer ThreadLocalPtrSTD<T>::mPtr = nullptr;

	CLAIRE_NAMESPACE_END
	CLAIRE_NAMESPACE_END
}

#endif
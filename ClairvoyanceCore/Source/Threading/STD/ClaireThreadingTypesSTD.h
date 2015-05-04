#ifndef CLAIRE_TRHEADING_TYPES_STD_H
#define CLAIRE_TRHEADING_TYPES_STD_H

#include "ClairePrerequisites.h"

#include "ClaireThreadSpecificPtrSTD.h"

namespace std
{
	class mutex;
	class recursive_mutex;
	template<class Mutex> class lock_guard;
	class thread;
}

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)
	CLAIRE_NAMESPACE_BEGIN(threading_internal)

	typedef std::mutex MutexImpl;
	typedef std::recursive_mutex RecursiveMutexImpl;
	template<class MutexType> using ScopedLockImpl = std::lock_guard<MutexType>;
	typedef std::thread ThreadImpl;
	template<class T> using ThreadSpecificPtrImpl = ThreadSpecificPtrSTD<T>;

	CLAIRE_NAMESPACE_END
	CLAIRE_NAMESPACE_END
}

#endif
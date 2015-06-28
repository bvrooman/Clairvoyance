#ifndef CLAIRE_THREADING_TYPES_BOOST_H
#define CLAIRE_THREADING_TYPES_BOOST_H

#include "ClairePrerequisites.h"

namespace boost
{
	class mutex;
	class recursive_mutex;
	namespace interprocess
	{
		template<class Mutex> class scoped_lock;
	}
	class thread;
	template<class T> class thread_specific_ptr;
}

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)
	CLAIRE_NAMESPACE_BEGIN(threading_internal)

	typedef boost::mutex MutexImpl;
	typedef boost::recursive_mutex RecursiveMutexImpl;
	template<class MutexType> using ScopedLockImpl = boost::interprocess::scoped_lock<MutexType>;
	typedef boost::thread ThreadImpl;
	template<class T> using ThreadLocalPtrImpl = boost::thread_specific_ptr<T>;

	CLAIRE_NAMESPACE_END
	CLAIRE_NAMESPACE_END
}


#endif
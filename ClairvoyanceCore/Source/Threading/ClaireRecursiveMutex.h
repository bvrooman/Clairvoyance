#ifndef CLAIRE_RECURSIVE_MUTEX_H
#define CLAIRE_RECURSIVE_MUTEX_H

#include "ClairePrerequisites.h"

#include "ClaireThreadingTypes.h"

#include "Idiom\ClairePimpl.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	class CLAIRE_CORE_EXPORT RecursiveMutex
	{
	public:
		CLAIRE_MOVABLE_ONLY(RecursiveMutex)

		typedef threading_internal::RecursiveMutexImpl MutexImpl;

		RecursiveMutex(void);
		~RecursiveMutex(void);

		void lock(void);
		void unlock(void);

		MutexImpl& operator*(void);

	private:
		Pimpl<MutexImpl> pRecursiveMutex;	
	};

	CLAIRE_NAMESPACE_END
}

#endif
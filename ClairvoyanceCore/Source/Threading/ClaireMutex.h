#ifndef CLAIRE_MUTEX_H
#define CLAIRE_MUTEX_H

#include "ClairePrerequisites.h"

#include "ClaireThreadingTypes.h"
#include "Idiom\ClairePimpl.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	class CLAIRE_CORE_EXPORT Mutex
	{
	public:
		CLAIRE_MOVABLE_ONLY(Mutex)

		typedef threading_internal::MutexImpl MutexImpl;

		Mutex(void);
		~Mutex(void);

		void lock(void);
		void unlock(void);

		// Get the mutex impl
		MutexImpl& operator*(void);

	private:
		Pimpl<MutexImpl> pMutex;
	};

	CLAIRE_NAMESPACE_END
}

#endif
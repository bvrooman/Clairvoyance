#include "ClaireThreadingIncludes.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)


	template<typename MutexType>
	ScopedLock<MutexType>::ScopedLock()
		: pScopedLock()
	{
	}

	template<typename MutexType>
	ScopedLock<MutexType>::~ScopedLock()
	{
	}

	template<typename MutexType>
	ScopedLock<MutexType>::ScopedLock(MutexType& mutex)
		: pScopedLock(*mutex)
	{
	}

	CLAIRE_NAMESPACE_END
}
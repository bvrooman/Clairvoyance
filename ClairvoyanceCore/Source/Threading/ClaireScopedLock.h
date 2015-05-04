#ifndef CLAIRE_SCOPED_LOCK_H
#define CLAIRE_SCOPED_LOCK_H

#include "ClairePrerequisites.h"

#include "ClaireThreadingTypes.h"
#include "Idiom\ClairePimpl.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	template<typename MutexType>
	class ScopedLock
	{
	public:
		CLAIRE_MOVABLE_ONLY(ScopedLock<MutexType>)

		typedef typename MutexType::MutexImpl MutexTypeImpl;
		using ScopedLockImpl = threading_internal::ScopedLockImpl<MutexTypeImpl>;

		ScopedLock(void);
		ScopedLock(MutexType& mutex);
		~ScopedLock(void);

	private:
		Pimpl<ScopedLockImpl> pScopedLock;
	};

	CLAIRE_NAMESPACE_END
}

#include "ClaireScopedLock.inl"

#endif
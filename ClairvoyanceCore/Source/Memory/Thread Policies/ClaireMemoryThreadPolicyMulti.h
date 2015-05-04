#ifndef CLAIRE_THREAD_POLICY_MULTI_H
#define CLAIRE_THREAD_POLICY_MULTI_H

#include "ClairePrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	template<typename SynchronizationPrimitive>
	class MemoryThreadPolicyMulti
	{
	public:
		CLAIRE_NON_COPYABLE(MemoryThreadPolicyMulti)

		MemoryThreadPolicyMulti(void){}

		inline void enter(void);
		inline void leave(void);

	private:
		SynchronizationPrimitive mPrimitive;
	};

	CLAIRE_NAMESPACE_END
}

#include "ClaireMemoryThreadPolicyMulti.inl"

#endif
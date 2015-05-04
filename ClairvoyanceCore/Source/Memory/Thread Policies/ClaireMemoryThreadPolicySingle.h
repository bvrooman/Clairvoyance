#ifndef CLAIRE_THREAD_POLICY_SINGLE_H
#define CLAIRE_THREAD_POLICY_SINGLE_H

#include "ClairePrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	class MemoryThreadPolicySingle
	{
	public:
		inline void enter(void) {};
		inline void leave(void) {};
	};

	CLAIRE_NAMESPACE_END
}

#endif
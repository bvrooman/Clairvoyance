#include "ClaireMemoryAllocationPolicyLinear.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	inline MemoryAllocationPolicyLinear::MemoryAllocationPolicyLinear(const void* start, const void* end)
	{
		mStart = start;
		mEnd = end;
		mCurrent = (void*)mStart;
	}

	inline MemoryAllocationPolicyLinear::~MemoryAllocationPolicyLinear(void)
	{

	}

	CLAIRE_NAMESPACE_END
}
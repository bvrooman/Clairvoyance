#include "ClaireMemoryBoundsCheckingPolicySimple.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	const byte MemoryBoundsCheckingPolicySimple::FRONT_BOUND_SIGNATURE[FRONT_BOUND_SIZE] = {FRONT_BOUND_TOKEN, FRONT_BOUND_TOKEN, FRONT_BOUND_TOKEN, FRONT_BOUND_TOKEN};
	const byte MemoryBoundsCheckingPolicySimple::END_BOUND_SIGNATURE[END_BOUND_SIZE] = {END_BOUND_TOKEN, END_BOUND_TOKEN, END_BOUND_TOKEN, END_BOUND_TOKEN};

	void MemoryBoundsCheckingPolicySimple::signFront(void* memory)
	{
		memcpy(memory, FRONT_BOUND_SIGNATURE, FRONT_BOUND_SIZE);
	}

	void MemoryBoundsCheckingPolicySimple::signEnd(void* memory)
	{
		memcpy(memory, END_BOUND_SIGNATURE, END_BOUND_SIZE);
	}

	bool MemoryBoundsCheckingPolicySimple::checkFrontSignature(void* memory) const
	{
		if(memcmp(memory, FRONT_BOUND_SIGNATURE, FRONT_BOUND_SIZE) != 0)
			return false;
		return true;
	}

	bool MemoryBoundsCheckingPolicySimple::checkEndSignature(void* memory) const
	{
		if(memcmp(memory, END_BOUND_SIGNATURE, END_BOUND_SIZE) != 0)
			return false;
		return true;
	}

	CLAIRE_NAMESPACE_END
}
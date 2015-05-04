#ifndef CLAIRE_MEMORY_BOUNDS_CHECKING_POLICY_NONE_H
#define CLAIRE_MEMORY_BOUNDS_CHECKING_POLICY_NONE_H

#include "ClairePrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	class MemoryBoundsCheckingPolicyNone
	{
	public:
		// Number of bytes in the start bound guard
		static const size_t FRONT_BOUND_SIZE = 0;
		// Number of bytes in the end bound guard
		static const size_t END_BOUND_SIZE = 0;

		static const size_t TOTAL_BOUND_SIZE = FRONT_BOUND_SIZE + END_BOUND_SIZE;

	public:
		void signFront(void* memory) {}
		void signEnd(void* memory) {}

		bool checkFrontSignature(void* memory) const { return true; }
		bool checkEndSignature(void* memory) const { return true; }
	};

	CLAIRE_NAMESPACE_END
}

#endif
#ifndef CLAIRE_MEMORY_BOUNDS_CHECKING_POLICY_SIMPLE_H
#define CLAIRE_MEMORY_BOUNDS_CHECKING_POLICY_SIMPLE_H

#include "ClairePrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	class CLAIRE_CORE_EXPORT MemoryBoundsCheckingPolicySimple
	{
	public:
		// Number of bytes in the start bound guard
		static const size_t FRONT_BOUND_SIZE = 4;
		// Number of bytes in the end bound guard
		static const size_t END_BOUND_SIZE = 4;

		static const size_t TOTAL_BOUND_SIZE = FRONT_BOUND_SIZE + END_BOUND_SIZE;

	public:
		void signFront(void* memory);
		void signEnd(void* memory);

		bool checkFrontSignature(void* memory) const;
		bool checkEndSignature(void* memory) const;

	private:
		static const byte FRONT_BOUND_TOKEN = 0xAF;
		static const byte END_BOUND_TOKEN = 0xFC;

		static const byte FRONT_BOUND_SIGNATURE[FRONT_BOUND_SIZE];
		static const byte END_BOUND_SIGNATURE[END_BOUND_SIZE];
	};

	CLAIRE_NAMESPACE_END
}

#endif
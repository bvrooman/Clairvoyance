#ifndef CLAIRE_MEMORY_ALLOCATION_POLICY_LINEAR_H
#define CLAIRE_MEMORY_ALLOCATION_POLICY_LINEAR_H

#include "ClaireMemoryAllocationPolicy.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	class CLAIRE_CORE_EXPORT MemoryAllocationPolicyLinear
		: public MemoryAllocationPolicy
	{
		CLAIRE_NON_COPYABLE(MemoryAllocationPolicyLinear)

	private:
		struct BlockHeader
		{
			size_t mAllocationSize;
		};

	public:
		template<typename U>
		struct rebind
		{
			typedef MemoryAllocationPolicyLinear other;
		};

	public:
		inline explicit MemoryAllocationPolicyLinear(const void* start, const void* end);
		inline ~MemoryAllocationPolicyLinear(void);

		size_t getAllocationSize(void* ptr) const CLAIRE_OVERRIDE;

	private:
		void* allocateImpl(size_t size) CLAIRE_OVERRIDE;
		void deallocateImpl(void* ptr) CLAIRE_OVERRIDE;

	private:
		const void* mStart;
		const void* mEnd;
		void* mCurrent;

	public:
		static const bool STL_ALLOCATOR_COMPATIBLE = true;
		static const bool ALLOCATED_OBJECT_COMPATIBLE = true;		
	};

	CLAIRE_NAMESPACE_END
}

#include "ClaireMemoryAllocationPolicyLinear.inl"

#endif
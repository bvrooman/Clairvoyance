#ifndef CLAIRE_MEMORY_ALLOCATION_POLICY_FREELIST_H
#define CLAIRE_MEMORY_ALLOCATION_POLICY_FREELIST_H

#include "ClaireMemoryAllocationPolicy.h"
#include "Containers\ClaireFreelist.h"
#include "Memory\ClaireHeapArea.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	template<typename T, size_t Overhead = 0>
	class MemoryAllocationPolicyFreelist
		: public MemoryAllocationPolicy
	{
	public:
		template<typename U>
		struct rebind
		{
			typedef MemoryAllocationPolicyFreelist<U, Overhead> other;
		};

	public:
		inline explicit MemoryAllocationPolicyFreelist(const void* start, const void* end);
		inline ~MemoryAllocationPolicyFreelist(void) {}

		size_t getAllocationSize(void* ptr) const CLAIRE_OVERRIDE;

	private:
		void* allocateImpl(size_t size) CLAIRE_OVERRIDE;
		void deallocateImpl(void* ptr) CLAIRE_OVERRIDE;

	public:
		static const bool STL_ALLOCATOR_COMPATIBLE = false;
		static const bool ALLOCATED_OBJECT_COMPATIBLE = false;

	private:
		static const size_t OVERHEAD = Overhead;

		Freelist* sFreelist;
		size_t mMaxAllocationSize;
	};

	template<typename T, size_t S, typename T2, size_t S2>
	inline bool operator == (const MemoryAllocationPolicyFreelist<T, S>&, const MemoryAllocationPolicyFreelist<T2, S>&)
	{
		return true;
	}
	template<typename T, size_t S, typename OtherAllocator>
	inline bool operator == (const MemoryAllocationPolicyFreelist<T, S>&, const OtherAllocator&)
	{ 
		return false; 
	}

	CLAIRE_NAMESPACE_END
}

#include "ClaireMemoryAllocationPolicyFreelist.inl"

#endif
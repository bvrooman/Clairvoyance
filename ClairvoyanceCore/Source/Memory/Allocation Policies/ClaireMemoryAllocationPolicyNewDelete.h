#ifndef CLAIRE_MEMORY_ALLOCATION_POLICY_NEW_DELETE_H
#define CLAIRE_MEMORY_ALLOCATION_POLICY_NEW_DELETE_H

#include "ClaireMemoryAllocationPolicy.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	class CLAIRE_CORE_EXPORT MemoryAllocationPolicyNewDelete
		: public MemoryAllocationPolicy
	{
	private:
		struct BlockHeader
		{
			size_t mAllocationSize;
		};

	public:
		template<typename U>
		struct rebind
		{
			typedef MemoryAllocationPolicyNewDelete other;
		};

	public:
		inline MemoryAllocationPolicyNewDelete(void) {}
		inline explicit MemoryAllocationPolicyNewDelete(const void* start, const void* end) {}
		inline ~MemoryAllocationPolicyNewDelete(void) {}

		size_t getAllocationSize(void* ptr) const CLAIRE_OVERRIDE;

	private:
		void* allocateImpl(size_t size) CLAIRE_OVERRIDE;
		void deallocateImpl(void* ptr) CLAIRE_OVERRIDE;

	public:
		static const bool STL_ALLOCATOR_COMPATIBLE = true;
		static const bool ALLOCATED_OBJECT_COMPATIBLE = true;
	};

	inline bool operator == (const MemoryAllocationPolicyNewDelete&, const MemoryAllocationPolicyNewDelete&)
	{
		return true;
	}
	template<typename OtherAllocator>
	inline bool operator == (const MemoryAllocationPolicyNewDelete&, const OtherAllocator&)
	{ 
		return false; 
	}

	CLAIRE_NAMESPACE_END
}

#include "ClaireMemoryAllocationPolicyNewDelete.inl"

#endif
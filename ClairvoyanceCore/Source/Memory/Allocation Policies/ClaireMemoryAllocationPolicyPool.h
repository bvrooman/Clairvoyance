#ifndef CLAIRE_MEMORY_ALLOCATION_POLICY_POOL_H
#define CLAIRE_MEMORY_ALLOCATION_POLICY_POOL_H

#include "ClaireMemoryAllocationPolicy.h"

#include "Memory\Pools\ClaireMemoryPool.h"
#include "Memory\Pools\ClaireStandardMemoryPool.h"
#include "Memory\Pools\ClaireMemoryPoolManager.h"

#include "Threading\ClaireThreadSpecificPtr.h"

#include "Memory\ClaireHeapArea.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	template<typename TPool>
	class MemoryAllocationPolicyPool
		: public MemoryAllocationPolicy
	{
		typedef TPool MemoryPoolType;

	public:
		template<typename U>
		struct rebind
		{
			typedef MemoryAllocationPolicyPool<MemoryPoolType> other;
		};

	public:
		inline explicit MemoryAllocationPolicyPool(const void* start, const void* end);
		inline ~MemoryAllocationPolicyPool(void) {}

		size_t getAllocationSize(void* ptr) const CLAIRE_OVERRIDE;

	protected:
		void* allocateImpl(size_t size) CLAIRE_OVERRIDE;
		void deallocateImpl(void* ptr) CLAIRE_OVERRIDE;

	private:
		static void initialize(const void* start, const void* end);

	public:
		static const bool STL_ALLOCATOR_COMPATIBLE = true;
		static const bool ALLOCATED_OBJECT_COMPATIBLE = true;

	private:
		static ThreadSpecificPtr<MemoryPool> sMemoryPool;

		static const string POLICY_NAME;
	};

	template<typename TPool>
	ThreadSpecificPtr<MemoryPool> MemoryAllocationPolicyPool<TPool>::sMemoryPool;

	template<typename TPool>
	const string MemoryAllocationPolicyPool<TPool>::POLICY_NAME = "MemoryAllocationPolicyPool";

	template<typename TPool, typename TPool2>
	inline bool operator == (const MemoryAllocationPolicyPool<TPool>&, const MemoryAllocationPolicyPool<TPool2>&)
	{
		return true;
	}
	template<typename TPool, typename OtherAllocator>
	inline bool operator == (const MemoryAllocationPolicyPool<TPool>&, const OtherAllocator&)
	{ 
		return false; 
	}

	CLAIRE_NAMESPACE_END
}

#include "ClaireMemoryAllocationPolicyPool.inl"

#endif
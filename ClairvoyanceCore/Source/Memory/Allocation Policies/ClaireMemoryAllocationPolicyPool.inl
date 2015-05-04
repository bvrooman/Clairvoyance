#include "Threading\ClaireThread.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	template<typename TPool>
	inline MemoryAllocationPolicyPool<TPool>::MemoryAllocationPolicyPool(const void* start, const void* end)
	{
		initialize(start, end);
	}

	template<typename TPool>
	inline void MemoryAllocationPolicyPool<TPool>::initialize(const void* start, const void* end)
	{
		if(sMemoryPool.get() == nullptr)
		{
			MemoryPool* pool = new MemoryPoolType(
				start,
				end);

			sMemoryPool.reset(pool);

			std::stringstream ss;
			ss << POLICY_NAME << this_thread::getID();
			string poolName = ss.str();
			MemoryPoolManager::getInstance()->addMemoryPool(poolName, pool);
		}
	}

	template<typename TPool>
	inline void* MemoryAllocationPolicyPool<TPool>::allocateImpl(size_t size)
	{
		return sMemoryPool->allocate(size);
	}

	template<typename TPool>
	inline void MemoryAllocationPolicyPool<TPool>::deallocateImpl(void* ptr)
	{
		sMemoryPool->deallocate(ptr);
	}

	template<typename TPool>
	inline size_t MemoryAllocationPolicyPool<TPool>::getAllocationSize(void* ptr) const
	{
		return sMemoryPool->getAllocationSize(ptr);
	}

	CLAIRE_NAMESPACE_END
}
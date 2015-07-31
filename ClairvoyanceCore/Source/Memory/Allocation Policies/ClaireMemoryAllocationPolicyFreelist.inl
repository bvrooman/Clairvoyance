namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	template<typename T, size_t Overhead>
	inline MemoryAllocationPolicyFreelist<T, Overhead>::MemoryAllocationPolicyFreelist(const void* start, const void* end)
	{
		size_t alignment = CLAIRE_ALIGN_OF(T);
		mMaxAllocationSize = sizeof(T) + alignment + OVERHEAD;

		sFreelist = new Freelist(
			start,
			end,
			mMaxAllocationSize);

	}

	template<typename T, size_t Overhead>
	inline void* MemoryAllocationPolicyFreelist<T, Overhead>::allocateImpl(size_t size)
	{
		if(size > mMaxAllocationSize)
		{
			throw std::bad_alloc();
		}

		return sFreelist->getBlock();
	}

	template<typename T, size_t Overhead>
	inline void MemoryAllocationPolicyFreelist<T, Overhead>::deallocateImpl(void* ptr)
	{
		sFreelist->returnBlock(ptr);
	}

	template<typename T, size_t Overhead>
	inline size_t MemoryAllocationPolicyFreelist<T, Overhead>::getAllocationSize(void* ptr) const
	{
		size_t userDataSize = mMaxAllocationSize;
		return userDataSize;
	}

	CLAIRE_NAMESPACE_END
}
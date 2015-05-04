namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	inline void* MemoryAllocationPolicyLinear::allocateImpl(size_t size)
	{
		union
		{
			void* asRaw;
			byte* asByte;
		};
		asRaw = mCurrent;

		BlockHeader header;
		header.mAllocationSize = size;
		// Append the header
		memcpy(asRaw, &header, sizeof(BlockHeader));

		// Return the memory after the header
		asByte += sizeof(BlockHeader);
		void* userPtr = asByte;

		asByte += size;
		mCurrent = asRaw;
		if(mCurrent >= mEnd)
		{
			throw std::bad_alloc();
		}

		return userPtr;
	}

	inline void MemoryAllocationPolicyLinear::deallocateImpl(void* ptr)
	{
		(void)ptr;
	}

	inline size_t MemoryAllocationPolicyLinear::getAllocationSize(void* ptr) const
	{
		union
		{
			void* asRaw;
			BlockHeader* asHeader;
		};
		
		asRaw = ptr;
		size_t userDataSize = asHeader[-1].mAllocationSize;
		return userDataSize;
	}

	CLAIRE_NAMESPACE_END
}
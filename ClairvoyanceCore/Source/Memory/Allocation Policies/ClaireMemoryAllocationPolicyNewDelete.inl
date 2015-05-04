namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	inline void* MemoryAllocationPolicyNewDelete::allocateImpl(size_t size)
	{
		union
		{
			void* asRaw;
			byte* asByte;
		};

		// Prefix the memory with a header to store metadata
		// Adjust the allocation size to fit a header
		size_t requiredSize = size + sizeof(BlockHeader);
		asRaw = ::operator new(requiredSize);
		void* originalAllocation = asRaw;

		BlockHeader header;
		header.mAllocationSize = size;
		// Append the header
		memcpy(asRaw, &header, sizeof(BlockHeader));

		// Return the memory after the header
		asByte += sizeof(BlockHeader);

		return asRaw;
	}

	inline void MemoryAllocationPolicyNewDelete::deallocateImpl(void* ptr)
	{
		union
		{
			void* asRaw;
			BlockHeader* asHeader;
		};

		// Include the block header in the delete call so we can delete it too
		asRaw = ptr;
		asHeader = &asHeader[-1];
		
		::operator delete(asRaw);
	}

	inline size_t MemoryAllocationPolicyNewDelete::getAllocationSize(void* ptr) const
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
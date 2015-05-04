namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	template<typename AllocationPolicy, typename ThreadPolicy, typename BoundsCheckingPolicy>
	MemoryArena<AllocationPolicy, ThreadPolicy, BoundsCheckingPolicy>::MemoryArena(void)
	{
	}

	template<typename AllocationPolicy, typename ThreadPolicy, typename BoundsCheckingPolicy>
	MemoryArena<AllocationPolicy, ThreadPolicy, BoundsCheckingPolicy>::MemoryArena(const void* start, const void* end)
		: mAllocationPolicy(start, end)
	{
	}

	template<typename AllocationPolicy, typename ThreadPolicy, typename BoundsCheckingPolicy>
	MemoryArena<AllocationPolicy, ThreadPolicy, BoundsCheckingPolicy>::~MemoryArena(void)
	{
	}

	template<typename AllocationPolicy, typename ThreadPolicy, typename BoundsCheckingPolicy>
	void* MemoryArena<AllocationPolicy, ThreadPolicy, BoundsCheckingPolicy>::allocate(size_t size, size_t alignment, size_t offset)
	{
		mThreadPolicy.enter();

		//
		// Determine the space needed for the allocation

		/*	The required size of the user requested memory we are allocating
			The required size of the user requested memory is equal to the
			requested size plus the size of overhead.
		*/
		const size_t requiredSize = size + OVERHEAD_REQUIREMENT;

		/*	The space to store the user allocation in
			Add the alignment to the allocation size so that there is room to
			shift the user requested memory to an aligned location.
		*/
		size_t space = requiredSize + alignment;

		/*	Allocate the space
			The amount of space actually allocated can be greater than the space
			if the allocation policy requires it.
		*/
		void* allocation = mAllocationPolicy.allocate(space);
		
		//
		// Determine the offset, align the memory, and adjust it with the offset

		union
		{
			void* asRaw;
			byte* asByte;
		};
		asRaw = allocation;

		/*	The size of the data that offsets the user requested allocation
			Any data that must be written to the buffer immediately before
			the user pointer (bookkeeping, bounds checking signatures, etc.) 
			will affect the alignment. 
			We want to align the user requested pointer, but not the overhead
			memory that offsets it. We find the size of the offset and get a
			location (pointer) in the buffer that represents this size.
			Finally, we align this pointer, giving us the required user
			pointer.
		*/
		offset += 
			sizeof(BlockHeader) +
			BoundsCheckingPolicy::FRONT_BOUND_SIZE;

		// Align the memory and offset it
		void* p = asByte + offset;
		assert(std::align(alignment, requiredSize, p, space));
		asRaw = std::align(alignment, requiredSize, p, space);
		asByte -= offset;
		assert(((uintptr_t)asRaw + offset) % alignment == 0);
		// N.B. align(asByte + offset) - offset >= asByte
		// Any memory before asByte is safe from being stomped

		/*	Get the difference between the aligned pointer minus offset and the original
			allocation
			This difference tells us the distance between the location of the aligned
			pointer minus offset and the location of the originally allocated memory. When 
			deallocating the memory, we must subtract this distance from the requested
			pointer we are deallocating in order to get the location of the original
			memory.
		*/
		size_t difference = (byte*)asByte - (byte*)allocation;
		// Store the difference in a header
		BlockHeader header;
		header.mAlignment = alignment;
		header.mAlignmentOffset = difference;
		// Append the header
		memcpy(asRaw, &header, sizeof(BlockHeader));
		asByte += sizeof(BlockHeader);

		// Sign the front bound
		mBoundsCheckingPolicy.signFront(asRaw);
		asByte += BoundsCheckingPolicy::FRONT_BOUND_SIZE;

		void* userPtr = asRaw;

		/*	Sign the end bound
			The location of the end bound is equal to the location of the start bound
			plus the allocated size, minus the overhead and alignment.
			The allocated size will equal the space (plus any any extra memory required
			by the allocation policy). Therefore, we subtract the overhead and alignment
			to get the requested size (with any extra policy-specific size requirements).
		*/
		asByte += mAllocationPolicy.getAllocationSize(allocation) - OVERHEAD_REQUIREMENT - alignment;
		mBoundsCheckingPolicy.signEnd(asRaw);

		mThreadPolicy.leave();

		return userPtr;
	}

	template<typename AllocationPolicy, typename ThreadPolicy, typename BoundsCheckingPolicy>
	void MemoryArena<AllocationPolicy, ThreadPolicy, BoundsCheckingPolicy>::deallocate(void* ptr)
	{
		if(!ptr)
		{
			return;
		}

		mThreadPolicy.enter();

		// Store a reference as byte to the original ptr being deallocated 
		byte* ptrAsByte = (byte*)ptr;

		union
		{
			void* asRaw;
			BlockHeader* asHeader;
			byte* asByte;
		};

		asRaw = ptr;
		
		// Shift the pointer backwards to include the front bound
		asByte -= BoundsCheckingPolicy::FRONT_BOUND_SIZE;
		byte* frontGuard = asByte;
		// Shift the pointer backwards to include the header
		asHeader = &asHeader[-1];
		BlockHeader header = *asHeader;
		// Shift the pointer backwards to include the offset created by alignment
		asByte -= header.mAlignmentOffset;

		size_t overhead =
			sizeof(BlockHeader) +
			BoundsCheckingPolicy::TOTAL_BOUND_SIZE;
		size_t allocationSize = mAllocationPolicy.getAllocationSize(asByte);
		byte* endGuard = ptrAsByte + allocationSize - overhead - header.mAlignment;

		assert(mBoundsCheckingPolicy.checkFrontSignature(frontGuard));
		assert(mBoundsCheckingPolicy.checkEndSignature(endGuard));
		
		mAllocationPolicy.deallocate(asByte);

		mThreadPolicy.leave();
	}

	CLAIRE_NAMESPACE_END
}
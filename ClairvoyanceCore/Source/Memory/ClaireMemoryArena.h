#ifndef CLAIRE_MEMORY_ARENA_H
#define CLAIRE_MEMORY_ARENA_H

#include "ClairePrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	template<typename AllocationPolicy, typename ThreadPolicy, typename BoundsCheckingPolicy>
	class MemoryArena
	{
		CLAIRE_NON_COPYABLE(MemoryArena)

	private:
		struct BlockHeader
		{
			size_t mAlignment;
			size_t mAlignmentOffset;
		};

	public:
		inline MemoryArena(void);
		inline explicit MemoryArena(const void* start, const void* end);
		inline ~MemoryArena(void);

		void* allocate(size_t size, size_t alignment, size_t offset);
		void deallocate(void* ptr);

	private:
		AllocationPolicy mAllocationPolicy;
		ThreadPolicy mThreadPolicy;
		BoundsCheckingPolicy mBoundsCheckingPolicy;

	public:
		static const bool STL_ALLOCATOR_COMPATIBLE = AllocationPolicy::STL_ALLOCATOR_COMPATIBLE;
		static const bool ALLOCATED_OBJECT_COMPATIBLE = AllocationPolicy::ALLOCATED_OBJECT_COMPATIBLE;

		static const size_t OVERHEAD_REQUIREMENT = sizeof(BlockHeader) + BoundsCheckingPolicy::TOTAL_BOUND_SIZE;
	};

	template <typename AllocationPolicy, typename ThreadPolicy, typename BoundsCheckingPolicy>
	using MemoryArenaUPtr = std::unique_ptr<MemoryArena<AllocationPolicy, ThreadPolicy, BoundsCheckingPolicy>>;

	template<typename BoundsCheckingPolicy>
	class MemoryArenaDetail
	{
	private:
		class MemoryAllocationPolicyDummy
		{
		public:
			static const bool STL_ALLOCATOR_COMPATIBLE = false;
			static const bool ALLOCATED_OBJECT_COMPATIBLE = false;
		};
		class MemoryThreadPolicyDummy {};
		typedef MemoryArena<
			MemoryAllocationPolicyDummy,
			MemoryThreadPolicyDummy,
			BoundsCheckingPolicy
		> Dummy;

	public:
		static const size_t OVERHEAD_REQUIREMENT = Dummy::OVERHEAD_REQUIREMENT;
	};

	CLAIRE_NAMESPACE_END
}

#include "ClaireMemoryArena.inl"

#endif 
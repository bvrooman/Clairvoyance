#ifndef CLAIRE_NODE_ALLOCATOR_H
#define CLAIRE_NODE_ALLOCATOR_H

#include "ClaireRenderingPrerequisites.h"

#include "Memory\ClaireHeapArea.h"
#include "Memory\Allocation Policies\ClaireMemoryAllocationPolicyFreelist.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_RENDERING_EXPORT IContiguousAllocator
	{
	public:
		virtual void* allocate(size_t sz) CLAIRE_ABSTRACT;
		virtual void deallocate(void* ptr) CLAIRE_ABSTRACT;
	};

	typedef std::unique_ptr<IContiguousAllocator> ContiguousAllocatorUPtr;
	typedef std::shared_ptr<IContiguousAllocator> ContiguousAllocatorSPtr;

	template<typename T>
	class ContiguousAllocator
		: public IContiguousAllocator
	{
	public:
		ContiguousAllocator(size_t sz)
			: mHeapArea(sz)
			, mAlloc(mHeapArea.getStart(), mHeapArea.getEnd())
		{
		}

		~ContiguousAllocator(void)
		{
		}

		void* allocate(size_t sz) CLAIRE_OVERRIDE
		{
			return mAlloc.allocate(sz);
		}

		void deallocate(void* ptr) CLAIRE_OVERRIDE
		{
			mAlloc.deallocate(ptr);
		}

	private:
		core::HeapArea mHeapArea;

		typedef T NodeType;
		typedef core::MemoryAllocationPolicyFreelist<NodeType> AllocationPolicy;
		AllocationPolicy mAlloc;
	};

	CLAIRE_NAMESPACE_END
}

#endif
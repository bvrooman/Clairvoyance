#include <gtest\gtest.h>

#include "Object.h"
#include "Memory\Allocation Policies\ClaireMemoryAllocationPolicyFreelist.h"
#include "Memory\ClaireHeapArea.h"

using namespace Claire::core;

TEST(AllocationPolicyFreeList, Allocate)
{
	HeapArea heap(1024);
	MemoryAllocationPolicyFreelist<Object> policy(heap.getStart(), heap.getEnd());
	
	void* p = policy.allocate(sizeof(Object));
	Object* obj = new (p) Object();
	obj->print();
	obj->~Object();
	policy.deallocate(p);
}

TEST(AllocationPolicyFreeList, AllocateBadAlloc)
{
	HeapArea heap(1024);
	MemoryAllocationPolicyFreelist<Object> policy(heap.getStart(), heap.getEnd());

	EXPECT_THROW(
	{
		void* p = policy.allocate(sizeof(Object) + 10);
		Object* obj = new (p)Object();
		obj->print();
		obj->~Object();
		policy.deallocate(p);
	},
	std::bad_alloc);
}
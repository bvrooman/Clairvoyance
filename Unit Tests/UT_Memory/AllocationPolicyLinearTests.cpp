#include <gtest\gtest.h>

#include "Object.h"
#include "Memory\Allocation Policies\ClaireMemoryAllocationPolicyLinear.h"
#include "Memory\ClaireHeapArea.h"

using namespace Claire::core;

TEST(AllocationPolicyLinear, Allocate)
{
	HeapArea heap(1024);
	MemoryAllocationPolicyLinear policy(heap.getStart(), heap.getEnd());

	void* p = policy.allocate(sizeof(Object));
	Object* obj = new (p)Object();
	obj->print();
	obj->~Object();
	policy.deallocate(p);
}

TEST(AllocationPolicyLinear, AllocateBadAlloc)
{
	HeapArea heap(1024);
	MemoryAllocationPolicyLinear policy(heap.getStart(), heap.getEnd());

	EXPECT_THROW(
	{
		void* p = policy.allocate(1025);
		Object* obj = new (p)Object();
		obj->print();
		obj->~Object();
		policy.deallocate(p);
	},
	std::bad_alloc);
}
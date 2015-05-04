#include <gtest\gtest.h>

#include "Object.h"
#include "Memory\Allocation Policies\ClaireMemoryAllocationPolicyNewDelete.h"

using namespace Claire::core;

TEST(AllocationPolicyNewDelete, Allocate)
{
	MemoryAllocationPolicyNewDelete policy;

	void* p = policy.allocate(sizeof(Object));
	Object* obj = new (p)Object();
	obj->print();
	obj->~Object();
	policy.deallocate(p);
}

TEST(AllocationPolicyNewDelete, AllocateBadAlloc)
{
	MemoryAllocationPolicyNewDelete policy;

	EXPECT_THROW(
	{	
		// 10 gb
		void* p = policy.allocate(1024 * 1024 * 1024 * 10);
		Object* obj = new (p)Object();
		obj->print();
		obj->~Object();
		policy.deallocate(p);
	},
	std::bad_alloc);
}
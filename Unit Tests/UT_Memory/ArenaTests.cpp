#include <gtest\gtest.h>

#include "Object.h"
#include "Memory\ClaireMemoryArena.h"

class DummyAllocPolicy
{
public:
	void* allocate(size_t sz)
	{
		lastAllocSize = sz;
		void* ptr = operator new(sz);
		return ptr;
	}

	void deallocate(void* ptr)
	{
		operator delete(ptr);
	}

	size_t getAllocationSize(void* ptr) const
	{
		(void)ptr;
		return lastAllocSize;
	}

	static int lastAllocSize;

	static const bool STL_ALLOCATOR_COMPATIBLE = false;
	static const bool ALLOCATED_OBJECT_COMPATIBLE = false;
};
int DummyAllocPolicy::lastAllocSize = 0;

class DummyThreadPolicy
{
public:
	inline void enter(void) {};
	inline void leave(void) {};
};

class DummyBoundsCheckPolicy
{
public:
	void signFront(void* memory) {}
	void signEnd(void* memory) {}

	bool checkFrontSignature(void* memory) const { return true; }
	bool checkEndSignature(void* memory) const { return true; }

	static const size_t FRONT_BOUND_SIZE = 0;
	static const size_t END_BOUND_SIZE = 0;
	static const size_t TOTAL_BOUND_SIZE = FRONT_BOUND_SIZE + END_BOUND_SIZE;
};

TEST(MemoryArena, AllocateDeallocate)
{
	using T = Object;
	using Alloc = DummyAllocPolicy;
	using Thr = DummyThreadPolicy;
	using BCP = DummyBoundsCheckPolicy;

	Claire::core::MemoryArena<Alloc, Thr, BCP> arena;

	EXPECT_NO_THROW(
	{
		// Allocate
		void* p = arena.allocate(sizeof(T), __alignof(T), 0);

		T* o = new (p)T();
		o->~T();

		// Deallocate
		arena.deallocate(p);
	});	
}
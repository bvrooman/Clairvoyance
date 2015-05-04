#include <gtest\gtest.h>

#include "Memory\Pools\ClaireStandardMemoryPool.h"

using namespace Claire::core;
using Claire::byte;

#if CLAIRE_TRASH_POOLS
TEST(StandardMemoryPool, TrashOnCreation)
{
	const size_t heapsz = 1024;
	StandardMemoryPool* pool = new StandardMemoryPool(heapsz);

	byte* ptr = (byte*)pool->allocate(1);
	// Read outside the allocated chunk to check the memory creation trashing
	ASSERT_EQ(pool->TRASH_ON_CREATION_SIGNATURE, *(ptr + 100));

	delete pool;
}

TEST(StandardMemoryPool, TrashOnAllocation)
{
	const size_t heapsz = 1024;
	StandardMemoryPool* pool = new StandardMemoryPool(heapsz);

	byte* ptr = (byte*)pool->allocate(1);
	ASSERT_EQ(pool->TRASH_ON_ALLOC_SIGNATURE, *ptr);

	delete pool;
}

TEST(StandardMemoryPool, TrashOnDeallocation)
{
	const size_t heapsz = 1024;
	StandardMemoryPool* pool = new StandardMemoryPool(heapsz);

	byte* ptr = (byte*)pool->allocate(1);
	pool->deallocate(ptr);
	ASSERT_EQ(pool->TRASH_ON_DEALLOC_SIGNATURE, *ptr);

	delete pool;
}
#endif

TEST(StandardMemoryPool, FullAllocationTest)
{
	const size_t heapsz = 1024;
	StandardMemoryPool* pool = new StandardMemoryPool(heapsz);

	byte* ptr = (byte*)pool->allocate(pool->getMaxAllocationSize());
	ASSERT_NE(nullptr, ptr);

	delete pool;
}

TEST(StandardMemoryPool, OverflowAllocationTest)
{
	const size_t heapsz = 1024;
	StandardMemoryPool* pool = new StandardMemoryPool(heapsz);

	byte* ptr = (byte*)pool->allocate(pool->getMaxAllocationSize() + 1);
	ASSERT_EQ(nullptr, ptr);

	delete pool;
}

TEST(StandardMemoryPool, AllocationDeallocationTest)
{
	const size_t heapsz = 1024;
	StandardMemoryPool* pool = new StandardMemoryPool(heapsz);

	int64_t originalSize = pool->getFreePoolSize();

	byte* block[4];
	block[0] = (byte*)pool->allocate(140);
	block[1] = (byte*)pool->allocate(70);
	block[2] = (byte*)pool->allocate(16);
	block[3] = (byte*)pool->allocate(1);

	pool->deallocate(block[0]);
	pool->deallocate(block[1]);
	pool->deallocate(block[2]);
	pool->deallocate(block[3]);

	ASSERT_EQ(originalSize, pool->getFreePoolSize());
}

TEST(StandardMemoryPool, SparseAllocationDeallocationTest)
{
	const size_t heapsz = 1024;
	StandardMemoryPool* pool = new StandardMemoryPool(heapsz);

	int64_t originalSize = pool->getFreePoolSize();

	byte* block[4];
	block[0] = (byte*)pool->allocate(512);
	block[1] = (byte*)pool->allocate(128);
	block[2] = (byte*)pool->allocate(64);
	block[3] = (byte*)pool->allocate(8);

	pool->deallocate(block[0]);
	pool->deallocate(block[2]);
	pool->deallocate(block[3]);
	pool->deallocate(block[1]);

	block[0] = (byte*)pool->allocate(128);
	block[1] = (byte*)pool->allocate(128);
	block[2] = (byte*)pool->allocate(128);
	pool->deallocate(block[1]);
	block[1] = (byte*)pool->allocate(64);
	block[3] = (byte*)pool->allocate(64);
	pool->deallocate(block[2]);
	block[2] = (byte*)pool->allocate(150);

	pool->deallocate(block[0]);
	pool->deallocate(block[1]);
	pool->deallocate(block[2]);
	pool->deallocate(block[3]);

	ASSERT_EQ(originalSize, pool->getFreePoolSize());
}

TEST(StandardMemoryPool, ZeroHeapAllocationTest)
{
	const size_t heapsz = 0;
	StandardMemoryPool* pool = new StandardMemoryPool(heapsz);

	byte* ptr = (byte*)pool->allocate(8);
	ASSERT_EQ(nullptr, ptr);

	delete pool;
}

TEST(StandardMemoryPool, SmallHeapAllocationTest)
{
	const size_t heapsz = 8;
	StandardMemoryPool* pool = new StandardMemoryPool(heapsz);

	byte* ptr = (byte*)pool->allocate(8);
	ASSERT_EQ(nullptr, ptr);

	delete pool;
}
#include "ClaireStandardMemoryPool.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	StandardMemoryPool::StandardMemoryPool(const void* start, const void* end)
		: mMemory(nullptr)
		, mUsePreallocatedMemory(true)
	{
		assert(end >= start);

		// Use preallocated memory
		mMemory = (void*)start;
		size_t size = (byte*)end - (byte*)start;
		if(size > 0)
		{
			initialize(size);
		}
	}

	StandardMemoryPool::StandardMemoryPool(size_t size)
		: mMemory(nullptr)
		, mUsePreallocatedMemory(false)
	{
		assert(size >= 0);

		// Allocate the total memory
		if(size > 0)
		{
			mMemory = ::operator new(size);
			initialize(size);
		}
	}

	void StandardMemoryPool::initialize(size_t size)
	{
		mFreePoolSize = size - sizeof(Chunk);
		mTotalPoolSize = size;

		if(mTrashOnCreation)
		{
			memset(mMemory, TRASH_ON_CREATION_SIGNATURE, size);
		}

		if(sizeof(Chunk) > size)
		{
			mFreePoolSize = 0;
		}
		// Only write the block if it is valid
		else
		{
			Chunk freeBlock(size - sizeof(Chunk));
			freeBlock.write(mMemory);
		}
	}

	StandardMemoryPool::~StandardMemoryPool(void)
	{
		if(!mUsePreallocatedMemory && mTotalPoolSize > 0)
		{
			::operator delete(mMemory);
		}
	}

	void* StandardMemoryPool::allocate(size_t size)
	{
		if(size > getMaxAllocationSize())
			return nullptr;
		
		size_t requiredSize = size + sizeof(Chunk);
		
		Chunk* block = (Chunk*)mMemory;
		
		// Find a block big enough for requested size
		while(block)
		{
			if(block->mFree && block->mDataSize >= requiredSize)
				break;
			block = block->mNext;
		}

		// If no block is found, return NULL
		if(!block)
			return nullptr;

		byte* blockData = (byte*)block;

		size_t freeDataSize = block->mDataSize - requiredSize;

		// If the block is valid, create a new free block with
		// what remains of the block memory
		if(freeDataSize > MIN_FREE_BLOCK_SIZE)
		{
			Chunk freeBlock(freeDataSize);
			freeBlock.mNext = block->mNext;
			freeBlock.mPrev = block;

			void* data = blockData + requiredSize;
			freeBlock.write(data);

			if(freeBlock.mNext)
				freeBlock.mNext->mPrev = (Chunk*)data;
			
			block->mNext = (Chunk*)data;
			block->mDataSize = size;
		}

		mFreePoolSize -= block->mDataSize;
		block->mFree = false;

		if(mTrashOnAlloc)
			memset(blockData + sizeof(Chunk), TRASH_ON_ALLOC_SIGNATURE, block->mDataSize);

		return blockData + sizeof(Chunk);
	}

	void StandardMemoryPool::deallocate(void* ptr)
	{
		if(!ptr)
			return;

		Chunk* block = (Chunk*)((byte*)ptr - sizeof(Chunk));

		// Check to see that the block isn't already free
		if(block->mFree)
			return;

		size_t fullBlockSize = block->mDataSize + sizeof(Chunk);
		mFreePoolSize += block->mDataSize;

		Chunk* head = block;
		Chunk* prev = block->mPrev;
		Chunk* next = block->mNext;

		// If the previous block is free, merge it with the current one
		if(block->mPrev && block->mPrev->mFree)
		{
			head = block->mPrev;
			prev = block->mPrev->mPrev;
			next = block->mNext;

			// Include the previous node in the block size if it is free
			// so we trash it as well
			fullBlockSize += block->mPrev->mDataSize + sizeof(Chunk);

			// If there is a next one, update its pointer
			if(block->mNext)
			{
				// Repoint the next
				block->mNext->mPrev = head;

				// Include the next node in the block size if it is free
				// so we trash it as well
				if(block->mNext->mFree)
				{
					next = block->mNext->mNext;
					if(block->mNext->mNext)
						block->mNext->mNext->mPrev = head;

					fullBlockSize += block->mNext->mDataSize + sizeof(Chunk);
				}
			}
		}

		else
		{
			// If the next node is free, merge it with the current one
			if(block->mNext && block->mNext->mFree)
			{
				head = block;
				prev = block->mPrev;
				next = block->mNext->mNext;

				// Include the next node in the block size so we trash it as well
				fullBlockSize += block->mNext->mDataSize + sizeof(Chunk);
			}
		}

		// Create the free block
		byte* freeBlockStart = (byte*)head;
		if(mTrashOnDealloc)
			memset(
				freeBlockStart,
				TRASH_ON_DEALLOC_SIGNATURE,
				fullBlockSize);

		size_t freeDataSize = fullBlockSize - sizeof(Chunk);

		Chunk freeBlock(freeDataSize);
		freeBlock.mPrev = prev;
		freeBlock.mNext = next;
		freeBlock.write(freeBlockStart);
	}

	size_t StandardMemoryPool::getAllocationSize(void* ptr)
	{
		union
		{
			void* asRaw;
			Chunk* asChunk;
		};

		// Point the user data backward to the Chunk header
		Chunk* block = (Chunk*)((byte*)ptr - sizeof(Chunk));

		// Return the user data size recorded in the Chunk
		size_t userDataSize = block->mDataSize;
		return userDataSize;
	}

	size_t StandardMemoryPool::getMaxAllocationSize(void) const
	{
		if(sizeof(Chunk) > mFreePoolSize)
		{
			return 0;
		}
		return (size_t)mFreePoolSize - sizeof(Chunk);
	}

	void StandardMemoryPool::dumpToFile(void) const
	{
	}

	CLAIRE_NAMESPACE_END
}

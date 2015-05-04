#ifndef CLAIRE_MEMORY_POOL
#define CLAIRE_MEMORY_POOL

#include "ClairePrerequisites.h"

/**	The code herein is based upon the tutorial provided by
	Marco Alamia.
	http://www.codinglabs.net/tutorial_memory_pool.aspx
**/

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

#define CLAIRE_TRASH_POOLS_DEBUG 1
#define CLAIRE_TRASH_POOLS_RELEASE 0

/** Trashing the memory pool is useful for checking its
	state.
	"The idea here is to copy a pattern in the user data block
	on allocation and on deallocation. Doing this we can easily
	see if the chunk has been used or not and in what state it
	was left.
	Since trashing requires a memory copy every time, we do
	not want to use it outside of debug environments."
**/
#if CLAIRE_DEBUG
#	define CLAIRE_TRASH_POOLS CLAIRE_TRASH_POOLS_DEBUG
#else
#	define CLAIRE_TRASH_POOLS CLAIRE_TRASH_POOLS_RELEASE
#endif

	class CLAIRE_CORE_EXPORT MemoryPool
	{
	public:
		MemoryPool(void)
			: mTotalPoolSize(0)
			, mFreePoolSize(0)
			, mTrashOnCreation(CLAIRE_TRASH_POOLS)
			, mTrashOnAlloc(CLAIRE_TRASH_POOLS)
			, mTrashOnDealloc(CLAIRE_TRASH_POOLS)
		{}

		virtual ~MemoryPool(void)
		{}

		inline virtual void* allocate(size_t size) CLAIRE_ABSTRACT;
		inline virtual void deallocate(void* ptr) CLAIRE_ABSTRACT;

		inline virtual void dumpToFile(void) const CLAIRE_ABSTRACT;

		// Get the size that was requested when allocating ptr
		inline virtual size_t getAllocationSize(void* ptr) CLAIRE_ABSTRACT;

		inline int64_t getTotalPoolSize(void) const { return mTotalPoolSize; }
		inline int64_t getFreePoolSize(void) const { return mFreePoolSize; }
		
		inline virtual size_t getMaxAllocationSize(void) const CLAIRE_ABSTRACT;

	protected:
		int64_t mTotalPoolSize;
		int64_t mFreePoolSize;

		bool mTrashOnCreation;
		bool mTrashOnAlloc;
		bool mTrashOnDealloc;

	public:
		static const byte TRASH_ON_CREATION_SIGNATURE = 0xCC;
		static const byte TRASH_ON_ALLOC_SIGNATURE = 0xAB;
		static const byte TRASH_ON_DEALLOC_SIGNATURE = 0xFE;
	};

	typedef std::unique_ptr<MemoryPool> MemoryPoolUPtr;

	CLAIRE_NAMESPACE_END
}

#endif
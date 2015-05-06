#ifndef CLAIRE_MEMORY_POOL_STANDARD_H
#define CLAIRE_MEMORY_POOL_STANDARD_H

#include "ClairePrerequisites.h"

#include "ClaireMemoryPool.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	class CLAIRE_CORE_EXPORT StandardMemoryPool
		: public MemoryPool
	{
	public:
		inline StandardMemoryPool(const void* start, const void* end);
		inline StandardMemoryPool(size_t size);
		inline ~StandardMemoryPool(void);

		inline void* allocate(size_t size) CLAIRE_OVERRIDE;
		inline void deallocate(void* ptr) CLAIRE_OVERRIDE;

		inline size_t getAllocationSize(void* ptr) CLAIRE_OVERRIDE;

		inline size_t getMaxAllocationSize(void) const CLAIRE_OVERRIDE;

		inline void dumpToFile(void) const CLAIRE_OVERRIDE;

	private:
		inline void initialize(size_t size);

	private:
		void* mMemory = nullptr;
		bool mUsePreallocatedMemory = false;

	private:
		static const size_t MIN_FREE_BLOCK_SIZE = 16;

	public:
		class Chunk
		{
		public:
			Chunk(size_t sz)
				: mDataSize(sz)
			{}

			void write(void* dest) { memcpy(dest, this, sizeof(Chunk)); }
			void read(void* src) { memcpy(this, src, sizeof(Chunk)); }

		public:
			Chunk* mNext = nullptr;
			Chunk* mPrev = nullptr;
			size_t mDataSize = 0;
			bool mFree = true;
		};
	};

	CLAIRE_NAMESPACE_END
}

#endif


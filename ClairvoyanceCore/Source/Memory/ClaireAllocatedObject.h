#ifndef CLAIRE_ALLOCATED_OBJECT_H
#define CLAIRE_ALLOCATED_OBJECT_H

#include "Threading\ClaireThreadLocalPtr.h"

// Undefine new and delete in case of any other #define new or #define delete
#ifdef new
#	undef new
#endif
#ifdef delete
#	undef delete
#endif

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	template<typename Arena, typename HeapArea>
	class AllocatedObject
	{
	public:
		explicit AllocatedObject(void)
		{
		}

		virtual ~AllocatedObject(void)
		{
		}

		void* operator new(size_t sz)
		{
			initializeTLS();
			size_t alignment = getAlignmentFromSize(sz);
			return sArena->allocate(sz, alignment, 0);
		}

		void* operator new(size_t sz, void* ptr)
		{
			(void)sz;
			return ptr;
		}

		void* operator new[](size_t sz)
		{
			initializeTLS();
			size_t alignment = getAlignmentFromSize(sz);
			return sArena->allocate(sz, alignment, 0);
		}

		void* operator new[](size_t sz, void* ptr)
		{
			(void)sz;
			return ptr;
		}

		void operator delete(void* ptr)
		{
			sArena->deallocate(ptr);
		}

		void operator delete(void* ptr, void*)
		{
			sArena->deallocate(ptr);
		}

		void operator delete[](void* ptr)
		{
			sArena->deallocate(ptr);
		}

		void operator delete[](void* ptr, void*)
		{
			sArena->deallocate(ptr);
		}

	private:
		static ThreadLocalPtr<HeapArea> sHeapArea;
		static ThreadLocalPtr<Arena> sArena;

	private:
		static size_t getHeapAreaSize(void)
		{
			return 8 * 1024 *1024;
		}

		static void initializeTLS(void)
		{
			if(sHeapArea.get() == nullptr)
			{
				size_t sz = getHeapAreaSize();
				sHeapArea.reset(
					new HeapArea(sz)
					);
			}
			if(sArena.get() == nullptr)
			{
				sArena.reset(
					new Arena(
						sHeapArea->getStart(), 
						sHeapArea->getEnd()
						)
					);
			}
		}

		static size_t getAlignmentFromSize(size_t sz)
		{
			size_t value = sz ^ (sz & (sz - 1));
			return value;
		}
	};

	template<typename Arena, typename HeapArea>
	ThreadLocalPtr<HeapArea> AllocatedObject<Arena, HeapArea>::sHeapArea;

	template<typename Arena, typename HeapArea>
	ThreadLocalPtr<Arena> AllocatedObject<Arena, HeapArea>::sArena;

	CLAIRE_NAMESPACE_END
}

#endif
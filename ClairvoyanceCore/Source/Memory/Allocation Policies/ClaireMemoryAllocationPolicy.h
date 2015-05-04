#ifndef CLAIRE_MEMORY_ALLOCATION_POLICY_H
#define CLAIRE_MEMORY_ALLOCATION_POLICY_H

#include "ClairePrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	class CLAIRE_CORE_EXPORT MemoryAllocationPolicy
	{
	public:
		inline virtual ~MemoryAllocationPolicy() {}

		virtual size_t getAllocationSize(void* ptr) const CLAIRE_ABSTRACT;

		inline void* allocate(size_t sz)
		{
			return allocateImpl(sz);
		}

		inline void deallocate(void* ptr)
		{
			deallocateImpl(ptr);
		}

	protected:
		virtual void* allocateImpl(size_t size) CLAIRE_ABSTRACT;
		virtual void deallocateImpl(void* ptr) CLAIRE_ABSTRACT;

	};

	CLAIRE_NAMESPACE_END
}

#endif


#ifndef CLAIRE_MEMORY_OBJECT_TRAITS_H
#define CLAIRE_MEMORY_OBJECT_TRAITS_H

#include "ClairePrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	template<typename T>
	class MemoryObjectTraits
	{
	public:
		template<typename U>
		struct rebind
		{
			typedef MemoryObjectTraits<U> other;
		};

	public:
		inline explicit MemoryObjectTraits() {}
		inline ~MemoryObjectTraits() {}
		template<typename U> inline explicit MemoryObjectTraits(const MemoryObjectTraits<U>&) {}

		// Address
		inline T* address(T& r)
		{
			return &r;
		}
		inline T const* address(const T& r)
		{
			return &r;
		}

		inline void construct(T* p, const T& t)
		{
			new (p) T(t);
		}
		inline void destroy(T* p)
		{
			p->~T();
		}
	};

	CLAIRE_NAMESPACE_END
}

#endif
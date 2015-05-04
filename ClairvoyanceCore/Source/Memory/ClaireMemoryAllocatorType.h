#ifndef CLAIRE_MEMORY_ALLOCATOR_TYPE_H
#define CLAIRE_MEMORY_ALLOCATOR_TYPE_H

#include "ClairePrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	template<typename T>
	struct MemoryAllocatorTypeBase
	{
		typedef T value_type;
	};

	template<typename T>
	class MemoryAllocatorType
		: public MemoryAllocatorTypeBase<T>
	{
	public:
		typedef MemoryAllocatorTypeBase<T>	Base;
		typedef typename Base::value_type	value_type;
		typedef value_type*					pointer;
		typedef const value_type*			const_pointer;
		typedef value_type&					reference;
		typedef const value_type&			const_reference;
		typedef std::size_t					size_type;
		typedef std::ptrdiff_t				difference_type;
	};

	CLAIRE_NAMESPACE_END
}

#endif
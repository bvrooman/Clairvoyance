#ifndef CLAIRE_MEMORY_ALLOCATOR_STL_H
#define CLAIRE_MEMORY_ALLOCATOR_STL_H

#include "ClaireMemoryAllocatorType.h"
#include "ClaireMemoryObjectTraits.h"
#include "Allocation Policies\ClaireMemoryAllocationPolicyNewDelete.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)
	
	template
		<
		typename T,
		typename AllocationPolicy = MemoryAllocationPolicyNewDelete,
		typename Traits = MemoryObjectTraits<T>
		>
	class MemoryAllocatorSTL
		: public MemoryAllocatorType<T>
		, public Traits
	{
	public:
		typedef typename MemoryAllocatorType::value_type		value_type;
		typedef typename MemoryAllocatorType::pointer			pointer;
		typedef typename MemoryAllocatorType::const_pointer		const_pointer;
		typedef typename MemoryAllocatorType::reference			reference;
		typedef typename MemoryAllocatorType::const_reference	const_reference;
		typedef typename MemoryAllocatorType::size_type			size_type;
		typedef typename MemoryAllocatorType::difference_type	difference_type;

	public:
		template<typename U>
		struct rebind
		{
			typedef MemoryAllocatorSTL
				<
				U, 
				typename AllocationPolicy::template rebind<U>::other, 
				typename Traits::template rebind<U>::other
				> other;
		};

	public:
		inline explicit MemoryAllocatorSTL() {}
		virtual ~MemoryAllocatorSTL() {}

		inline MemoryAllocatorSTL(const MemoryAllocatorSTL& rhs):Traits(rhs) {}

		template<typename U>
		inline MemoryAllocatorSTL(const MemoryAllocatorSTL<U>&) {}

		template<typename U, typename UP, typename UT>
		inline MemoryAllocatorSTL(const MemoryAllocatorSTL<U, UP, UT>& rhs):Traits(rhs) {}

		size_type max_size() const
		{
			return std::numeric_limits<size_type>::max();
		}

		inline pointer allocate(
			size_type count,
			typename std::allocator<void>::const_pointer ptr = 0)
		{
			(void)ptr;
			size_type sz = count * sizeof(value_type);
			pointer p = static_cast<pointer>(
				mAllocationPolicy.allocate(sz)
				);
			if(!p)
				throw std::bad_alloc();
			return p;
		}

		inline void deallocate(pointer ptr, size_type)
		{
			mAllocationPolicy.deallocate(ptr);
		}

	private:
		AllocationPolicy mAllocationPolicy;
	};

	template<typename T, typename P, typename Tr>
	inline bool operator == (const MemoryAllocatorSTL<T, P, Tr>& lhs, const MemoryAllocatorSTL<T, P, Tr>& rhs)
	{ 
		return true; 
	}

	template<typename T, typename P, typename Tr, typename T2, typename P2, typename Tr2>
	inline bool operator == (const MemoryAllocatorSTL<T, P, Tr>& lhs, const MemoryAllocatorSTL<T2, P2, Tr2>& rhs)
	{
		return false;
	}

	template<typename T, typename P, typename Tr, typename OtherMemoryAllocator>
	inline bool operator == (const MemoryAllocatorSTL<T, P, Tr>& lhs, const OtherMemoryAllocator& rhs)
	{ 
		return false;
	}

	template<typename T, typename P, typename Tr>
	inline bool operator != (const MemoryAllocatorSTL<T, P, Tr>& lhs, const MemoryAllocatorSTL<T, P, Tr>& rhs)
	{ 
		return !operator == (lhs, rhs); 
	}

	template<typename T, typename P, typename Tr, typename T2, typename P2, typename Tr2>
	inline bool operator != (const MemoryAllocatorSTL<T, P, Tr>& lhs, const MemoryAllocatorSTL<T2, P2, Tr2>& rhs)
	{ 
		return !operator == (lhs, rhs); 
	}

	template<typename T, typename P, typename Tr, typename OtherMemoryAllocator>
	inline bool operator != (const MemoryAllocatorSTL<T, P, Tr>& lhs, const OtherMemoryAllocator& rhs)
	{ 
		return !operator == (lhs, rhs); 
	}

	CLAIRE_NAMESPACE_END
}

#endif
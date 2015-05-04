#ifndef CLAIRE_STL_CONTAINERS_H
#define CLAIRE_STL_CONTAINERS_H

#include "Memory\ClaireMemoryAllocatorSTL.h"

#include "Memory\Allocation Policies\ClaireMemoryAllocationPolicyNewDelete.h"
#include "Memory\Allocation Policies\ClaireMemoryAllocationPolicyFreelist.h"

namespace Claire
{
	using namespace core;
	//CLAIRE_NAMESPACE_BEGIN(core)

	// A wrapper to make setting the STL allocator policies convienent:
	// Changing the general policy will change all STL containers that use it.
	//
	// E.g.
	// MemoryAllocationPolicyNewDelete
	typedef MemoryAllocationPolicyNewDelete DefaultSTLAllocationPolicy;

	typedef DefaultSTLAllocationPolicy VectorAllocationPolicy;
	typedef DefaultSTLAllocationPolicy ListAllocationPolicy;
	typedef DefaultSTLAllocationPolicy SetAllocationPolicy;
	typedef DefaultSTLAllocationPolicy MapAllocationPolicy;

	// Some allocation policies are not compatible with STL allocation,
	// such as MemoryAllocationPolicyFreelist. Generally, a policy is
	// incompatible if it cannot allocate a variable size block
	static_assert(VectorAllocationPolicy::STL_ALLOCATOR_COMPATIBLE, "The allocation policy cannot be used in an STL Allocator.");
	static_assert(ListAllocationPolicy::STL_ALLOCATOR_COMPATIBLE, "The allocation policy cannot be used in an STL Allocator.");
	static_assert(SetAllocationPolicy::STL_ALLOCATOR_COMPATIBLE, "The allocation policy cannot be used in an STL Allocator.");
	static_assert(MapAllocationPolicy::STL_ALLOCATOR_COMPATIBLE, "The allocation policy cannot be used in an STL Allocator.");

#if CLAIRE_CONTAINERS_USE_CUSTOM_MEMORY_ALLOCATOR
	template<typename T, typename A = MemoryAllocatorSTL<T, VectorAllocationPolicy>> using vector = std::vector<T, A>;
	template<typename T, typename A = MemoryAllocatorSTL<T, ListAllocationPolicy>> using list = std::list<T, A>;
	template <typename T, typename P = std::less<T>, typename A = MemoryAllocatorSTL<T, SetAllocationPolicy>> using set = std::set<T, P, A>;
	template <typename K, typename V, typename P = std::less<K>, typename A = MemoryAllocatorSTL<std::pair<const K, V>, MapAllocationPolicy>> using map = std::map<K, V, P, A>;
#else
	template<typename T> using vector = std::vector<T>;
	template<typename T> using list = std::list<T>;
	template<typename T, typename P = std::less<T>> using set = std::set<T, P>;
	template<typename T, typename H = std::hash<T>, typename P = std::equal_to<T>> using unordered_set = std::unordered_set <T, H, P>;
	template <typename K, typename V, typename P = std::less<K>> using map = std::map<K, V, P>;
	template <typename K, typename V, typename H = std::hash<K>, typename P = std::equal_to<K>> using unordered_map = std::unordered_map < K, V, H, P > ;
#endif
	//CLAIRE_NAMESPACE_END
}

#endif
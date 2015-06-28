#ifndef CLAIRE_MEMORY_CONFIG_H
#define CLAIRE_MEMORY_CONFIG_H

#include "ClaireAllocatedObject.h"

#include "ClaireMemoryArena.h"

#include "Allocation Policies\ClaireMemoryAllocationPolicyNewDelete.h"
#include "Allocation Policies\ClaireMemoryAllocationPolicyPool.h"
#include "Allocation Policies\ClaireMemoryAllocationPolicyLinear.h"

#include "Bounds Checking Policies\ClaireMemoryBoundsCheckingPolicySimple.h"
#include "Bounds Checking Policies\ClaireMemoryBoundsCheckingPolicyNone.h"


#include "Thread Policies\ClaireMemoryThreadPolicyMulti.h"
#include "Thread Policies\ClaireMemoryThreadPolicySingle.h"

#include "Pools\ClaireStandardMemoryPool.h"

#include "ClaireMemoryArena.h"
#include "ClaireHeapArea.h"
#include "Threading\ClaireThreadLocalPtr.h"

#include "Idiom\ClaireDummy.h"

#include "Threading\ClaireMutex.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	using BCPSimple = MemoryBoundsCheckingPolicySimple;
	using BCPNone = MemoryBoundsCheckingPolicyNone;

#if CLAIRE_DEBUG
	using BCPolicy = BCPSimple;
#else
	using BCPolicy = BCPNone;
#endif

	using ThreadPolicyMulti			= MemoryThreadPolicyMulti<Mutex>;
	using ThreadPolicySingle		= MemoryThreadPolicySingle;
	using ThreadPolicy				= ThreadPolicySingle;


	template<size_t Index>
	class IndexedHeapArea
	{
	public:
		enum
		{
			Index = Index
		};

	public:
		IndexedHeapArea(size_t sz)
		{
 			mHeapArea = std::make_unique<HeapArea>(sz);
		}

		inline void* getStart(void) const { return mHeapArea->getStart(); }
		inline void* getEnd(void) const { return mHeapArea->getEnd(); }

	private:
		HeapAreaUPtr mHeapArea;
	};

	using MemoryArenaNewDelete		= MemoryArena<MemoryAllocationPolicyNewDelete,					ThreadPolicy, BCPolicy>;
	using MemoryArenaPool			= MemoryArena<MemoryAllocationPolicyPool<StandardMemoryPool>,	ThreadPolicy, BCPolicy>;
	using MemoryArenaLinear			= MemoryArena<MemoryAllocationPolicyLinear,						ThreadPolicy, BCPolicy>;

	using AllocatedObjectNewDelete	= AllocatedObject<MemoryArenaNewDelete,	IndexedHeapArea<0>>;
	using AllocatedObjectPool		= AllocatedObject<MemoryArenaPool,		IndexedHeapArea<1>>;
	using AllocatedObjectLinear		= AllocatedObject<MemoryArenaLinear,	IndexedHeapArea<2>>;

	using GeneralAllocatedObject	= AllocatedObjectNewDelete;
	//using GeneralAllocatedObject	= AllocatedObjectLinear; 


	// Compile time check if the policy is valid for superclassing AllocatedObject
	//typedef GeneralAllocatedObject<Dummy> DummyGeneralAllocatedObject;
	//static_assert(DummyGeneralAllocatedObject::ALLOCATED_OBJECT_COMPATIBLE, "The allocation policy cannot be used in the superclass MemoryArena for AllocatedObject.");

	CLAIRE_NAMESPACE_END
}

#endif
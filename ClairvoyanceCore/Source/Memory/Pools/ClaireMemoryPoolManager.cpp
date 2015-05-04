#include "ClaireMemoryPoolManager.h"

#include "Memory\Pools\ClaireMemoryPool.h"

#include "ClaireStandardMemoryPool.h"
#include "Memory\Bounds Checking Policies\ClaireMemoryBoundsCheckingPolicySimple.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	Singleton<MemoryPoolManager>::TypeUPtr Singleton<MemoryPoolManager>::mInstance;

	MemoryPoolManager::MemoryPoolManager(void)
	{
	}

	MemoryPoolManager::~MemoryPoolManager(void)
	{
	}

	void MemoryPoolManager::addMemoryPool(const string& name, MemoryPool* pool)
	{
		mManagerImpl.attach(name, pool);
	}

	MemoryPool* MemoryPoolManager::getMemoryPool(const string& name)
	{
		return mManagerImpl.get(name);
	}

	CLAIRE_NAMESPACE_END
}
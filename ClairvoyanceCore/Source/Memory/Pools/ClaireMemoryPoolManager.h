#ifndef CLAIRE_MEMORY_POOL_MANAGER_H
#define CLAIRE_MEMORY_POOL_MANAGER_H

#include "ClairePrerequisites.h"

#include "Idiom\ClaireSingleton.h"
#include "Idiom\ClaireManager.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	class MemoryPool;

	class CLAIRE_CORE_EXPORT MemoryPoolManager
		: public Singleton<MemoryPoolManager>
	{
		CLAIRE_SINGLETON_FRIEND

	public:
		static MemoryPoolManager* getInstance(void)
		{
			return Singleton<MemoryPoolManager>::getInstance();
		}

	public:
		void addMemoryPool(const string& name, MemoryPool* pool);
		MemoryPool* getMemoryPool(const string& name);

	protected:
		MemoryPoolManager(void);
		~MemoryPoolManager(void);

	private:
		typedef Manager<MemoryPool, string> MemoryPoolManagerImpl;
		MemoryPoolManagerImpl mManagerImpl;
	};

	CLAIRE_NAMESPACE_END
}

#endif
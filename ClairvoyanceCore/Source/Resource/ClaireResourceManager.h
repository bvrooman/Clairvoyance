#ifndef CLAIRE_RESOURCE_MANAGER_H
#define CLAIRE_RESOURCE_MANAGER_H

#include "ClairePrerequisites.h"
#include "Idiom\ClaireManager.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	class Resource;

	class CLAIRE_CORE_EXPORT ResourceManager
	{
		CLAIRE_MOVABLE_ONLY(ResourceManager)

	public:
		ResourceManager(void);
		virtual ~ResourceManager(void);

		Resource* getResource(const string& name) const;

		Resource* createResource(
			const string& name,
			const string& path
			);
		Resource* loadResource(
			const string& name,
			const string& path
			);

	protected:
		virtual Resource* createResource_(
			const string& name,
			const string& path
			) CLAIRE_ABSTRACT;

	protected:
		typedef core::OwningManager<Resource, string> ResourceManagerImpl;
		ResourceManagerImpl mManagerImpl;
	};

	typedef std::unique_ptr<ResourceManager> ResourceManagerUPtr;

	CLAIRE_NAMESPACE_END
}

#endif
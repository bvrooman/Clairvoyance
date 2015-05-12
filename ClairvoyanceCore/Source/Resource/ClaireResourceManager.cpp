#include "ClaireResourceManager.h"
#include "ClaireResource.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	Resource* ResourceManager::getResource(const string& name) const
	{
		return mManagerImpl.get(name);
	}

	Resource* ResourceManager::createResource(
		const string& name,
		const string& path
		)
	{
		return createResource_(name, path);
	}
	Resource* ResourceManager::loadResource(
		const string& name,
		const string& path
		)
	{
		Resource* resource = createResource(name, path);
		resource->load();
		return resource;
	}

	CLAIRE_NAMESPACE_END
}
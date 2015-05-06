#include "ClaireResource.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(core)

	Resource::Resource(const string& name, const string& path, ResourceManager* manager)
		: mName(name)
		, mPath(path)
		, mManager(manager)
	{

	}

	Resource::~Resource(void)
	{

	}

	void Resource::load(void)
	{
		if(mLoaded)
			return;

		preload_();
		load_();
		postload_();
		calculateSize();
	}

	void Resource::unload(void)
	{
		unload_();
		calculateSize();
	}

	CLAIRE_NAMESPACE_END
}
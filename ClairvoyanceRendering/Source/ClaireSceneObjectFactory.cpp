#include "ClaireSceneObjectFactory.h"
#include "ClaireSceneObject.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	SceneObjectFactory::SceneObjectFactory(void)
	{
	}

	SceneObjectFactory::~SceneObjectFactory(void)
	{
	}

	SceneObject* SceneObjectFactory::createSceneObject(const string& name, const ParamMap* params)
	{
		return createSceneObject_(name, params);
	}

	CLAIRE_NAMESPACE_END
}
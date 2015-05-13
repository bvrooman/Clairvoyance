#include "ClaireSceneManager.h"
#include "ClaireScene.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)
	
	SceneManager::SceneManager(MeshManager* meshManager)
		: mMeshManager(meshManager)
	{
	}

	Scene* SceneManager::createScene(const string& name)
	{
		assert(mActiveRenderSystem);

		return mManagerImpl.create<Scene>(
			name,
			name, mActiveRenderSystem, this
			);
	}

	void SceneManager::destroyScene(const string& name)
	{
		mManagerImpl.destroy(name);
	}

	CLAIRE_NAMESPACE_END
}
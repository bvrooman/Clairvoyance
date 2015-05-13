#ifndef CLAIRE_SCENE_MANAGER_H
#define CLAIRE_SCENE_MANAGER_H

#include "ClaireRenderingPrerequisites.h"
#include "Idiom\ClaireManager.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class Scene;
	class RenderSystem;
	class MeshManager;

	class CLAIRE_RENDERING_EXPORT SceneManager
	{
		CLAIRE_MOVABLE_ONLY(SceneManager)

	public:
		SceneManager(MeshManager* meshManager);
		~SceneManager(void) = default;

		Scene* createScene(const string& name);
		void destroyScene(const string& name);

		void setRenderSystem(RenderSystem* renderSystem) { mActiveRenderSystem = renderSystem; }

		MeshManager* getMeshManager(void) const { return mMeshManager; }

	private:
		typedef OwningManager<Scene, string> SceneManagerImpl;
		SceneManagerImpl mManagerImpl;

		MeshManager* mMeshManager;

		RenderSystem* mActiveRenderSystem;

	};
	typedef std::unique_ptr<SceneManager> SceneManagerUPtr;

	CLAIRE_NAMESPACE_END
}

#endif
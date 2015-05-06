#ifndef CLAIRE_SCENE_H
#define CLAIRE_SCENE_H

#include "ClaireRenderingPrerequisites.h"

#include "Idiom\ClaireManager.h"

#include "ClaireCamera.h"
#include "ClaireSceneObjectFactory.h"
#include "ClaireEntity.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class SceneManager;
	class RenderSystem;
	class Viewport;

	class CLAIRE_RENDERING_EXPORT Scene
	{
		CLAIRE_MOVABLE_ONLY(Scene)

	public:
		Scene(
			const string& name,
			RenderSystem* renderSystem,
			SceneManager* manager
			);
		virtual ~Scene(void);

		Camera* createCamera(const string& name);
		void* destroyCamera(const string& name);
		void attachCamera(CameraUPtr camera);
		CameraUPtr detachCamera(const string& name);

		Entity* createEntity(const string& name, const string& meshName);

		void renderScene(Camera* camera, Viewport* viewport);

		string getName(void) const { return mName; }

	private:
		void setViewport(Viewport* viewport);

	private:
		SceneManager* mManager = nullptr;
		string mName;

		RenderSystem* mRenderSystem;

		typedef OwningManager<Camera, string> CameraManagerImpl;
		CameraManagerImpl mCameraManagerImpl;

		const Camera* mCurrentCamera = nullptr;
		const Viewport* mCurrentViewport = nullptr;

		// Scene object factories
		SceneObjectFactoryUPtr mEntityFactory;
	};

	typedef std::unique_ptr<Scene> SceneUPtr;

	CLAIRE_NAMESPACE_END
}

#endif
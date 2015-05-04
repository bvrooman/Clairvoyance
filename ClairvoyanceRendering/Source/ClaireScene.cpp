#include "ClaireScene.h"
#include "ClaireSceneManager.h"

#include "ClaireRenderSystem.h"
#include "ClaireViewport.h"

#include "ClaireEntity.h"
#include "ClaireEntityFactory.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	Scene::Scene(
		const string& name,
		RenderSystem* renderSystem,
		SceneManager* manager
		)
		: mName(name)
		, mRenderSystem(renderSystem)
		, mManager(manager)
		, mCurrentCamera(nullptr)
		, mCurrentViewport(nullptr)
	{
		mEntityFactory = std::make_unique<EntityFactory>(mManager->getMeshManager());
	}

	Scene::~Scene(void)
	{
	}

	Camera* Scene::createCamera(const string& name)
	{
		return mCameraManagerImpl.create<Camera>(
			name,
			name, this
			);
	}

	void Scene::attachCamera(CameraUPtr camera)
	{
		string name = camera->getName();
		mCameraManagerImpl.attach(
			name,
			std::move(camera)
			);
	}

	CameraUPtr Scene::detachCamera(const string& name)
	{
		return mCameraManagerImpl.detach(name);
	}

	Entity* Scene::createEntity(const string& name, const string& meshName)
	{
		SceneObjectFactory::ParamMap* paramMap = new SceneObjectFactory::ParamMap();
		paramMap->insert(SceneObjectFactory::ParamMap::value_type(
			EntityFactory::MESH_NAME_KEY,
			meshName
			));

		SceneObject* sceneObject = mEntityFactory->createSceneObject(name, paramMap);
		return static_cast<Entity*>(sceneObject);
	}

	void Scene::renderScene(Camera* camera, Viewport* viewport)
	{
		setViewport(viewport);

		// Clear the current frame buffer before rendering
		mRenderSystem->clearFrameBuffer(mCurrentViewport->getBackgroundColour());
		
		// Render
		mRenderSystem->render();
	}

	void Scene::setViewport(Viewport* viewport)
	{
		mCurrentViewport = viewport;
		mRenderSystem->setViewport(viewport);
	}

	CLAIRE_NAMESPACE_END
}
#include "ClaireRenderRoot.h"

#include "ClaireWindowEvents.h"

#include "ClaireRenderSystem.h"
#include "ClaireRenderWindow.h"

#include "Resource\ClaireResourceManager.h"
#include "Mesh\ClaireMeshManager.h"

#include "ClairePlugin.h"

namespace Claire
{
	Singleton<rendering::RenderRoot>::TypeUPtr Singleton<rendering::RenderRoot>::mInstance = 0;

	CLAIRE_NAMESPACE_BEGIN(rendering)
	
	RenderRoot::RenderRoot(void)
	{
	}

	RenderRoot::~RenderRoot(void)
	{
	}

	void RenderRoot::initialize(void)
	{
		mMeshManager = std::make_unique<MeshManager>(mActiveRenderSystem->getBufferObjectManager());
		
		mSceneManager = std::make_unique<SceneManager>((MeshManager*)mMeshManager.get());
		mSceneManager->setRenderSystem(mActiveRenderSystem);
	}

	void RenderRoot::shutdown(void)
	{
		stopRendering();

		// Delete the SceneManager
		SceneManagerUPtr s = std::move(mSceneManager);
	}

	void RenderRoot::addPlugin(Plugin* plugin)
	{
		mPluginVector.push_back(plugin);
	}

	void RenderRoot::installAllPlugins(void)
	{
		for(auto&& plugin : mPluginVector)
		{
			plugin->install(this);
		}
	}

	void RenderRoot::startRendering(void)
	{
		mRendering = true;
		while(mRendering)
		{
			WindowEvents::messageHandler();
			renderFrame();
		}
	}

	void RenderRoot::stopRendering(void)
	{
		mRendering = false;
	}

	void RenderRoot::renderFrame(void)
	{
		update();
	}

	void RenderRoot::update(void)
	{
		//mActiveRenderSystem->updateAllRenderTargets();
		//mActiveRenderSystem->swapAllRenderTargetBuffers();
		mActiveRenderSystem->update();
	}

	void RenderRoot::setRenderSystem(RenderSystem* renderSystem)
	{
		if(!renderSystem || renderSystem == mActiveRenderSystem)
		{
			return;
		}

		if(mActiveRenderSystem)
		{
			mActiveRenderSystem->shutdown();
		}

		mActiveRenderSystem = renderSystem;
		mActiveRenderSystem->initialize();
		mActiveRenderSystem->startup();

		if(mSceneManager)
		{
			mSceneManager->setRenderSystem(mActiveRenderSystem);
		}
	}

	void RenderRoot::setRenderSystem(const string& name)
	{
		RenderSystem* system = getRenderSystem(name);
		setRenderSystem(system);
	}

	void RenderRoot::addRenderSystem(RenderSystem* renderSystem)
	{
		mInstalledRenderSystemMap.insert(RenderSystemMap::value_type(
			renderSystem->getName(),
			renderSystem
			));
	}

	void RenderRoot::removeRenderSystem(const string& name)
	{
		for(auto it = mInstalledRenderSystemMap.begin(), end = mInstalledRenderSystemMap.end(); it != end; it++)
		{
			if(it->first == name)
			{
				mInstalledRenderSystemMap.erase(it);
				break;
			}
		}
	}

	RenderSystem* RenderRoot::getRenderSystem(const string& name) const
	{
		auto it = mInstalledRenderSystemMap.find(name);
		if(it != mInstalledRenderSystemMap.end())
		{
			return it->second;
		}
		return nullptr;
	}

	RenderSystem* RenderRoot::getActiveRenderSystem(void) const
	{
		return mActiveRenderSystem;
	}

	RenderWindow* RenderRoot::createRenderWindow(const string& name, size_t width, size_t height, bool fullscreen)
	{
		RenderWindow* window;
		window = mActiveRenderSystem->createRenderWindow(
			name,
			width,
			height,
			fullscreen
			);
		if(!mMainRenderWindow)
		{
			setMainRenderWindow(window);
		}
		return window;
	}

	void RenderRoot::setMainRenderWindow(RenderWindow* window)
	{
		if(window)
		{
			if(mMainRenderWindow)
			{
				mMainRenderWindow->removeRenderWindowEventListener(this);
			}

			mMainRenderWindow = window;
			mMainRenderWindow->addRenderWindowEventListener(this);
		}
	}

	void RenderRoot::onWindowClose(const RenderWindowEvent& event)
	{
		if(event.getRenderWindow() == mMainRenderWindow)
		{
			shutdown();
		}
	}

	CLAIRE_NAMESPACE_END
}
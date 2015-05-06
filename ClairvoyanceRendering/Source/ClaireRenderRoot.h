#ifndef CLAIRE_RENDER_ROOT_H
#define CLAIRE_RENDER_ROOT_H

#include "ClaireRenderingPrerequisites.h"
#include "Memory\ClaireMemoryConfig.h"

#include "Idiom\ClaireSingleton.h"

#include "Resource\ClaireResourceManager.h"
#include "Mesh\ClaireMeshManager.h"

#include "ClaireRenderWindow.h"
#include "ClaireRenderSystem.h"

#include "ClaireScene.h"
#include "ClaireSceneManager.h"

#include "ClaireIRenderWindowEventListener.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class Plugin;

	class CLAIRE_RENDERING_EXPORT RenderRoot
		//: public GeneralAllocatedObject
		: public IRenderWindowEventListener
	{
	public:
		RenderRoot(void);
		~RenderRoot(void);

		void initialize(void);
		void shutdown(void);

		void addPlugin(Plugin* plugin);

		void installAllPlugins(void);

		void startRendering(void);
		void renderFrame(void);
		void update(void);
		
		void stopRendering(void);

		void setRenderSystem(RenderSystem* renderSystem);
		void setRenderSystem(const string& name);

		void addRenderSystem(RenderSystem* renderSystem);
		void removeRenderSystem(const string& name);

		RenderSystem* getRenderSystem(const string& name) const;
		RenderSystem* getActiveRenderSystem(void) const;

		RenderWindow* createRenderWindow(const string& name, size_t width, size_t height, bool fullscreen);
		void setMainRenderWindow(RenderWindow* window);

		void onWindowMove(const RenderWindowEvent& event) CLAIRE_OVERRIDE {}
		void onWindowResize(const RenderWindowEvent& event) CLAIRE_OVERRIDE {}
		void onWindowClose(const RenderWindowEvent& event) CLAIRE_OVERRIDE;

		SceneManager* getSceneManager(void) const { return mSceneManager.get(); }

		MeshManager* getMeshManager(void) const { return static_cast<MeshManager*>(mMeshManager.get()); }

	private:
		typedef vector<Plugin*> PluginVector;
		PluginVector mPluginVector;

		/*
		Who owns the Render System?
		Render Systems are owned by the client application that
		adds (installs) it. No lifetime management should be done
		within the engine itself.
		*/
		typedef map<string, RenderSystem*> RenderSystemMap;
		RenderSystemMap mInstalledRenderSystemMap;
		RenderSystem* mActiveRenderSystem = nullptr;

		// Owned resource managers
		ResourceManagerUPtr mMeshManager = nullptr;

		// Scene manager
		SceneManagerUPtr mSceneManager = nullptr;
		
		bool mRendering = false;

		RenderWindow* mMainRenderWindow = nullptr;
	};

	using RenderRootUPtr = std::unique_ptr<RenderRoot>;

	CLAIRE_NAMESPACE_END

}

#endif
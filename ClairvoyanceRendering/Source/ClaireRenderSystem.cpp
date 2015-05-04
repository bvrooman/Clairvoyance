#include "ClaireRenderSystem.h"


namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	RenderSystem::RenderSystem(
		const string& name,
		const WindowPlatformSupport* windowPlatformSupport,
		const WindowRendererSupport* windowRendererSupport
		)
		: mName(name)
		, mRenderWindowManager(
			windowPlatformSupport,
			windowRendererSupport,
			&mRenderTargetManager
			)
		, mInitialized(false)
		, mActiveViewport(nullptr)
	{	
	}

	RenderSystem::~RenderSystem(void)
	{
	}

	void RenderSystem::initialize(void)
	{
		if(mInitialized)
			return;

		mInitialized = true;
	}

	void RenderSystem::startup(void)
	{

	}

	void RenderSystem::update(void)
	{
		mRenderTargetManager.updateAllRenderTargets();
		mRenderTargetManager.swapAllRenderTargetBuffers();
	}

	void RenderSystem::shutdown(void)
	{
	}

	RenderWindow* RenderSystem::createRenderWindow(const string& name, size_t width, size_t height, bool fullscreen)
	{
		return mRenderWindowManager.createRenderWindow(name, width, height, fullscreen);
	}

	void RenderSystem::destroyRenderWindow(const string& name)
	{
		mRenderWindowManager.destroyRenderWindow(name);
	}

	RenderWindow* RenderSystem::getRenderWindow(const string& name) const
	{
		return mRenderWindowManager.getRenderWindow(name);
	}

	CLAIRE_NAMESPACE_END
}
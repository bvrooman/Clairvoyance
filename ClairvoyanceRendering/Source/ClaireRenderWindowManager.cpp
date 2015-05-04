#include "ClaireRenderWindowManager.h"

#include "ClaireWindowPlatformSupport.h"
#include "ClaireWindowRendererSupport.h"
#include "ClaireRenderTargetManager.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	RenderWindowManager::RenderWindowManager(
		const WindowPlatformSupport* platformSupport,
		const WindowRendererSupport* rendererSupport,
		RenderTargetManager* renderTargetManager
		)
		: mPlatformSupport(platformSupport)
		, mRendererSupport(rendererSupport)
		, mRenderTargetManager(renderTargetManager)
	{
	}

	RenderWindowManager::~RenderWindowManager(void)
	{
	}

	RenderWindow* RenderWindowManager::createRenderWindow(const string& name, size_t width, size_t height, bool fullscreen)
	{
		auto window = std::make_unique<RenderWindow>(
			mPlatformSupport,
			mRendererSupport,
			name, width, height, fullscreen,
			this
			);
		window->create();
		RenderWindow* window_ = window.get();
		mRenderTargetManager->attachRenderTarget(std::move(window));
		return window_;
	}

	void RenderWindowManager::destroyRenderWindow(const string& name)
	{
		// RAII destruction
		mRenderTargetManager->detachRenderTarget(name);
	}

	RenderWindow* RenderWindowManager::getRenderWindow(const string& name) const
	{
		return static_cast<RenderWindow*>(mRenderTargetManager->getRenderTarget(name));
	}


	CLAIRE_NAMESPACE_END
}
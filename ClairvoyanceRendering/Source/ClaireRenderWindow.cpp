#include "ClaireRenderWindow.h"

#include "ClaireRenderSystem.h"
#include "ClaireWindowPlatformSupport.h"
#include "ClaireWindowRendererSupport.h"

#include "ClaireIRenderWindowEventListener.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	RenderWindow::RenderWindow(
		const WindowPlatformSupport* platformSupport,
		const WindowRendererSupport* rendererSupport,
		string name, size_t width, size_t height, bool fullscreen,
		RenderWindowManager* manager
		)
		: RenderTarget(name, width, height)
		, mPlatformSupport(platformSupport)
		, mRendererSupport(rendererSupport)
		, mFullscreen(fullscreen)
		, mManager(manager)
	{
		mPlatformComponent = mPlatformSupport->createWindowPlaformComponent(this);
		mRendererComponent = mRendererSupport->createWindowRendererComponent(this);
	}

	RenderWindow::~RenderWindow(void)
	{
	}

	void RenderWindow::create(void)
	{
		mPlatformComponent->create();

		// Set the pixel format before creating the render component
		mRendererSupport->setPixelFormat(mPlatformComponent->getDeviceContext(), *mPixelFormat.get());

		mRendererComponent->create();
	}

	void RenderWindow::swapBuffers(void)
	{
		mPlatformComponent->swapBuffers();
	}

	void RenderWindow::addRenderWindowEventListener(IRenderWindowEventListener* listener)
	{
		mRenderWindowEventListeners.insert(listener);
	}

	void RenderWindow::removeRenderWindowEventListener(IRenderWindowEventListener* listener)
	{
		mRenderWindowEventListeners.erase(listener);
	}

	void RenderWindow::notifyOnResize(void)
	{
		RenderWindowEvent event(this);
		std::for_each(mRenderWindowEventListeners.begin(), mRenderWindowEventListeners.end(), [&](IRenderWindowEventListener* listener)
		{
			listener->onWindowResize(event);
		});
	}

	void RenderWindow::notifyOnMove(void)
	{
		RenderWindowEvent event(this);
		std::for_each(mRenderWindowEventListeners.begin(), mRenderWindowEventListeners.end(), [&](IRenderWindowEventListener* listener)
		{
			listener->onWindowMove(event);
		});
	}

	void RenderWindow::notifyOnClose(void)
	{
		RenderWindowEvent event(this);
		std::for_each(mRenderWindowEventListeners.begin(), mRenderWindowEventListeners.end(), [&](IRenderWindowEventListener* listener)
		{
			listener->onWindowClose(event);
		});
	}


	CLAIRE_NAMESPACE_END
}
#ifndef CLAIRE_RENDER_WINDOW_H
#define CLAIRE_RENDER_WINDOW_H

#include "ClaireRenderingPrerequisites.h"
#include "ClaireRenderTarget.h"

#include "ClaireWindowPlatformComponent.h"
#include "ClaireWindowRendererComponent.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class RenderWindowManager;
	class WindowPlatformSupport;
	class WindowRendererSupport;
	class IRenderWindowEventListener;

	class CLAIRE_RENDERING_EXPORT RenderWindow
		: public RenderTarget
	{
	public:
		RenderWindow(
			const WindowPlatformSupport* platformSupport,
			const WindowRendererSupport* rendererSupport,
			string name, size_t width, size_t height, bool fullscreen,
			RenderWindowManager* manager
			);
		~RenderWindow(void) = default;

		void create(void);

		void swapBuffers(void) CLAIRE_OVERRIDE;

		const WindowPlatformComponent* getPlatformComponent(void) const { return mPlatformComponent.get(); }
		const WindowRendererComponent* getRendererComponent(void) const { return mRendererComponent.get(); }

		bool getFullscreen(void) const { return mFullscreen; }

		void notifyOnResize(void);
		void notifyOnMove(void);
		void notifyOnClose(void);

		void addRenderWindowEventListener(IRenderWindowEventListener* listener);
		void removeRenderWindowEventListener(IRenderWindowEventListener* listener);

		RenderWindowManager* getManager(void) const { return mManager; }

	protected:
		bool mFullscreen;

		const WindowPlatformSupport* mPlatformSupport;
		const WindowRendererSupport* mRendererSupport;

		RenderWindowManager* mManager;

		WindowPlatformComponentUPtr mPlatformComponent;
		WindowRendererComponentUPtr mRendererComponent;

		set<IRenderWindowEventListener*> mRenderWindowEventListeners;
	};

	typedef std::unique_ptr<RenderWindow> RenderWindowUPtr;

	CLAIRE_NAMESPACE_END
}

#endif
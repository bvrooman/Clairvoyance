#ifndef CLAIRE_RENDER_WINDOW_MANAGER_H
#define CLAIRE_RENDER_WINDOW_MANAGER_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireRenderWindow.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class WindowPlatformSupport;
	class WindowRendererSupport;
	class RenderTargetManager;

	class CLAIRE_RENDERING_EXPORT RenderWindowManager
	{
	public:
		RenderWindowManager(
			const WindowPlatformSupport* platformSupport,
			const WindowRendererSupport* rendererSupport,
			RenderTargetManager* renderTargetManager
			);
		~RenderWindowManager(void);

		RenderWindow* createRenderWindow(const string& name, size_t width, size_t height, bool fullscreen);
		void destroyRenderWindow(const string& name);

		RenderWindow* getRenderWindow(const string& name) const;

	private:
		const WindowPlatformSupport* mPlatformSupport;
		const WindowRendererSupport* mRendererSupport;
		RenderTargetManager* mRenderTargetManager;
	};

	CLAIRE_NAMESPACE_END
}

#endif
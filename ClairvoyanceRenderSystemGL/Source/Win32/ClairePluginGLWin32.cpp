#include "ClairePluginGLWin32.h"

#include "Win32\ClaireWindowPlatformSupportWin32.h"
#include "Win32\ClaireWindowRendererSupportGLWin32.h"
#include "ClaireRenderSystemGL.h"
#include "ClaireRenderRoot.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	PluginGLWin32::PluginGLWin32(void)
	{
		mWindowPlatformSupport = std::make_unique<WindowPlatformSupportWin32>();
		mWindowRendererSupport = std::make_unique<WindowRendererSupportGLWin32>();

		mRenderSystem = std::make_unique<RenderSystemGL>(
			mWindowPlatformSupport.get(),
			mWindowRendererSupport.get()
			);

		mWindowRendererSupport->initialize();
	}

	PluginGLWin32::~PluginGLWin32(void)
	{
	}

	void PluginGLWin32::install(RenderRoot* renderRoot)
	{
		renderRoot->addRenderSystem(mRenderSystem.get());
	}

	void PluginGLWin32::uninstall(RenderRoot* renderRoot)
	{
		renderRoot->removeRenderSystem(mRenderSystem->getName());
	}

	CLAIRE_NAMESPACE_END
}
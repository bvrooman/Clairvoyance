#ifndef CLAIRE_PLUGIN_GL_WIN32_H
#define CLAIRE_PLUGIN_GL_WIN32_H

#include "ClaireGLPrerequisites.h"

#include "ClairePlugin.h"

#include "ClaireRenderSystem.h"
#include "ClaireWindowPlatformSupport.h"
#include "ClaireWindowRendererSupport.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_GL_EXPORT PluginGLWin32
		: public Plugin
	{
	public:
		PluginGLWin32(void);
		~PluginGLWin32(void);

		void install(RenderRoot* renderRoot) CLAIRE_OVERRIDE;
		void uninstall(RenderRoot* renderRoot) CLAIRE_OVERRIDE;

	private:
		WindowPlatformSupportUPtr mWindowPlatformSupport;
		WindowRendererSupportUPtr mWindowRendererSupport;
		RenderSystemUPtr mRenderSystem;
	};

	CLAIRE_NAMESPACE_END
}

#endif
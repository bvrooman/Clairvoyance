#ifndef CLAIRE_RENDER_SYSTEM_GL_H
#define CLAIRE_RENDER_SYSTEM_GL_H

#include "ClaireGLPrerequisites.h"

#include "ClaireRenderSystem.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_GL_EXPORT RenderSystemGL
		: public RenderSystem
	{
	public:
		RenderSystemGL(
			WindowPlatformSupport* windowPlatformSupport,
			WindowRendererSupport* windowRendererSupport);
		~RenderSystemGL(void) = default;

		void startup(void) CLAIRE_OVERRIDE;

		void render(void) CLAIRE_OVERRIDE;
		void setViewport(Viewport* viewport) CLAIRE_OVERRIDE;
		void clearFrameBuffer(const Colour& colour = Colour::Black) CLAIRE_OVERRIDE;
	};

	CLAIRE_NAMESPACE_END
}

#endif
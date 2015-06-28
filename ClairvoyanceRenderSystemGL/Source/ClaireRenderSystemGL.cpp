#include "ClaireRenderSystemGL.h"

#include "ClaireRenderContextGL.h"

#include "ClaireViewport.h"
#include "Buffers\ClaireBufferObjectManagerGL.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

		RenderSystemGL::RenderSystemGL(
			WindowPlatformSupport* windowPlatformSupport,
			WindowRendererSupport* windowRendererSupport
			)
		: RenderSystem(
			"RenderSystemGL",
			windowPlatformSupport,
			windowRendererSupport
			)
	{
		mBufferObjectManager = std::make_unique<BufferObjectManagerGL>();
	}

	void RenderSystemGL::startup(void)
	{
		
	}

	void RenderSystemGL::render(void)
	{
	}

	void RenderSystemGL::setViewport(Viewport* viewport)
	{
		if(mActiveViewport != viewport)
		{
			RenderTarget* target = viewport->getRenderTarget();
			mActiveViewport = viewport;

			GLsizei x, y, w, h;

			x = viewport->getLeftDim();
			y = viewport->getTopDim();
			w = viewport->getWidthDim();
			h = viewport->getHeightDim();

			glViewport(x, y, w, h);

			glScissor(x, y, w, h);
			glEnable(GL_SCISSOR_TEST);
		}
	}

	void RenderSystemGL::clearFrameBuffer(const Colour& colour)
	{
		GLbitfield flags = 0;

		flags |= GL_COLOR_BUFFER_BIT;
		glClearColor(colour.r, colour.g, colour.b, colour.a);

		flags |= GL_DEPTH_BUFFER_BIT;
		glClearDepth(1.0f);

		flags |= GL_STENCIL_BUFFER_BIT;

		glClear(flags);
	}

	CLAIRE_NAMESPACE_END
}
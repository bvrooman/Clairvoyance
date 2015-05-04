#ifndef CLAIRE_RENDER_CONTEXT_GL_WIN32_H
#define CLAIRE_RENDER_CONTEXT_GL_WIN32_H

#include "ClaireGLPrerequisites.h"

#include "ClaireRenderContextGL.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_GL_EXPORT RenderContextGLWin32
		: public RenderContextGL
	{
	public:
		RenderContextGLWin32(const DeviceContext* deviceContext);
		~RenderContextGLWin32(void);

		bool makeCurrent(void) CLAIRE_OVERRIDE;
		bool endCurrent(void) CLAIRE_OVERRIDE;
		bool release(void) CLAIRE_OVERRIDE;

	private:
		HGLRC mGLRC;
	};

	CLAIRE_NAMESPACE_END
}

#endif
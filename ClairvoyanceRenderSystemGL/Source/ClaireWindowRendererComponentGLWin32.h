#ifndef CLAIRE_WINDOW_RENDERER_COMPONENT_GL_WIN32_H
#define CLAIRE_WINDOW_RENDERER_COMPONENT_GL_WIN32_H

#include "ClaireGLPrerequisites.h"

#include "ClaireWindowRendererComponentGL.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_GL_EXPORT WindowRendererComponentGLWin32
		: public WindowRendererComponentGL
	{
	public:
		WindowRendererComponentGLWin32(RenderWindow* parentRenderWindow);
		~WindowRendererComponentGLWin32(void);

		void destroy(void) CLAIRE_OVERRIDE;

	protected:
		void createRenderContext(void) CLAIRE_OVERRIDE;

	private:
		HDC mHDC;
	};

	CLAIRE_NAMESPACE_END
}

#endif
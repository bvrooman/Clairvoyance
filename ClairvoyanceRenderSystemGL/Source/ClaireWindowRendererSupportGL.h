#ifndef CLAIRE_RENDERER_SUPPORT_GL_H
#define CLAIRE_RENDERER_SUPPORT_GL_H

#include "ClaireGLPrerequisites.h"

#include "ClaireWindowRendererSupport.h"

#include "ClaireWindowRendererComponent.h"
#include "ClaireRenderContextGL.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_GL_EXPORT WindowRendererSupportGL
		: public WindowRendererSupport
	{
	public:
		WindowRendererSupportGL(void);
		virtual ~WindowRendererSupportGL(void);
	};

	CLAIRE_NAMESPACE_END
}

#endif
#ifndef CLAIRE_WINDOW_RENDERER_COMPONENT_GL_H
#define CLAIRE_WINDOW_RENDERER_COMPONENT_GL_H

#include "ClaireGLPrerequisites.h"

#include "ClaireWindowRendererComponent.h"

#include "ClaireRenderContextGL.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)
	
	class CLAIRE_GL_EXPORT WindowRendererComponentGL
		: public WindowRendererComponent
	{
	public:
		using WindowRendererComponent::WindowRendererComponent;
		virtual ~WindowRendererComponentGL(void) = default;

		void create(void) CLAIRE_OVERRIDE;

		RenderContextGL* getRenderContextGL(void) const { return mRenderContext.get(); }

	protected:
		virtual void createRenderContext(void) CLAIRE_ABSTRACT;

	protected:
		RenderContextGLUPtr mRenderContext;
	};

	CLAIRE_NAMESPACE_END
}

#endif
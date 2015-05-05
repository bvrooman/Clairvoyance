#include "ClaireWindowRendererComponentGL.h"

#include "ClaireRenderWindow.h"
#include "ClaireWindowRendererSupport.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	WindowRendererComponentGL::WindowRendererComponentGL(RenderWindow* parentRenderWindow)
		: WindowRendererComponent(parentRenderWindow)
	{
	}

	WindowRendererComponentGL::~WindowRendererComponentGL(void)
	{
	}

	void WindowRendererComponentGL::create(void)
	{
		createRenderContext();
		bool success = mRenderContext->makeCurrent();
		assert(success);
	}

	CLAIRE_NAMESPACE_END
}
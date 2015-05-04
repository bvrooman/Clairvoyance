#include "ClaireRenderContextGL.h"

#include "Threading\ClaireThreadSpecificPtr.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	RenderContextGL::RenderContextGL(const DeviceContext* deviceContext)
		: mDeviceContext(deviceContext)
	{
	}

	RenderContextGL::~RenderContextGL(void)
	{
	}

	GLEWContext* glewGetContext(void)
	{
		static core::ThreadSpecificPtr<GLEWContext> sGLEWContext;

		if(sGLEWContext.get() == nullptr)
		{
			GLEWContext* context = new GLEWContext();
			sGLEWContext.reset(context);
			GLenum status = glewInit();
			if(status != GLEW_OK)
			{
				// Critical error
			}
		}
		return sGLEWContext.get();
	}

	CLAIRE_NAMESPACE_END
}


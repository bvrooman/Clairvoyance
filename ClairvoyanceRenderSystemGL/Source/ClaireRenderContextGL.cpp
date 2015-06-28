#include "ClaireRenderContextGL.h"

#include "Threading\ClaireThreadLocalPtr.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	RenderContextGL::RenderContextGL(const DeviceContext* deviceContext)
		: mDeviceContext(deviceContext)
	{
	}

	GLEWContext* glewGetContext(void)
	{
		static core::ThreadLocalPtr<GLEWContext> sGLEWContext;

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


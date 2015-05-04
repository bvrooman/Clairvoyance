#ifndef CLAIRE_RENDER_CONTEXT_GL_H
#define CLAIRE_RENDER_CONTEXT_GL_H

#include "ClaireGLPrerequisites.h"

#include "ClaireDeviceContext.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_GL_EXPORT RenderContextGL
	{
	public:
		RenderContextGL(const DeviceContext* deviceContext);
		virtual ~RenderContextGL(void);

		virtual bool makeCurrent(void) CLAIRE_ABSTRACT;
		virtual bool endCurrent(void) CLAIRE_ABSTRACT;
		virtual bool release(void) CLAIRE_ABSTRACT;

	protected:
		const DeviceContext* mDeviceContext;
	};

	typedef std::unique_ptr<RenderContextGL> RenderContextGLUPtr;

	CLAIRE_NAMESPACE_END
}



#endif
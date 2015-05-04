#ifndef CLAIRE_RENDERER_SUPPORT_GL_WIN32_H
#define CLAIRE_RENDERER_SUPPORT_GL_WIN32_H

#include "ClaireGLPrerequisites.h"

#include "ClaireWindowRendererSupportGL.h"


namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class DeviceContext;

	class CLAIRE_GL_EXPORT WindowRendererSupportGLWin32
		: public WindowRendererSupportGL
	{
	public:
		WindowRendererSupportGLWin32(void);
		~WindowRendererSupportGLWin32(void);

		void initialize(void) CLAIRE_OVERRIDE;

		WindowRendererComponentUPtr createWindowRendererComponent(RenderWindow* parentRenderWindow) const CLAIRE_OVERRIDE;

		void setPixelFormat(const DeviceContext* deviceContext, const PixelFormat& pixelFormat) const CLAIRE_OVERRIDE;

	private:
		bool initializeWGL(void);

	private:
		bool mHasPixelFormatARB;
		bool mHasMultisample;
		bool mHasHardwareGamma;
	};

	CLAIRE_NAMESPACE_END
}

#endif
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
		WindowRendererSupportGLWin32(void) = default;
		~WindowRendererSupportGLWin32(void);

		void initialize(void) CLAIRE_OVERRIDE;

		WindowRendererComponentUPtr createWindowRendererComponent(RenderWindow* parentRenderWindow) const CLAIRE_OVERRIDE;

		void setPixelFormat(const DeviceContext* deviceContext, const PixelFormat& pixelFormat) const CLAIRE_OVERRIDE;

		void startDummyContext(void);
		void endDummyContext(void);

	private:
		bool initializeWGL(void);

	private:
		LPCWSTR mDummyText = L"dummy";
		HWND mDummyHWND;
		RenderContextGLUPtr mDummyRenderContext;

		bool mHasPixelFormatARB = false;
		bool mHasMultisample = false;
		bool mHasHardwareGamma = false;
	};

	CLAIRE_NAMESPACE_END
}

#endif
#include "ClaireRenderContextGLWin32.h"
#include "Win32\ClaireDeviceContextWin32.h"

#include "Threading\ClaireThreadLocalPtr.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	RenderContextGLWin32::RenderContextGLWin32(const DeviceContext* deviceContext)
		: RenderContextGL(deviceContext)
	{
		HDC hdc = static_cast<const DeviceContextWin32*>(mDeviceContext)->getHDC();

		// first, get context from hdc?
		mGLRC = wglCreateContext(hdc);
	}

	bool RenderContextGLWin32::makeCurrent(void)
	{
		HDC hdc = static_cast<const DeviceContextWin32*>(mDeviceContext)->getHDC();
		bool success = wglMakeCurrent(hdc, mGLRC);
		return success;
	}

	bool RenderContextGLWin32::endCurrent(void)
	{
		bool success = wglMakeCurrent(nullptr, nullptr);
		return success;
	}

	bool RenderContextGLWin32::release(void)
	{
		bool success = false;
		if(mGLRC != nullptr)
		{
			success = wglDeleteContext(mGLRC);
			mGLRC = nullptr;
		}
		return success;
	}

	WGLEWContext* wglewGetContext(void)
	{
		static core::ThreadLocalPtr<WGLEWContext> sWGLEWContext;

		if(sWGLEWContext.get() == nullptr)
		{
			WGLEWContext* context = new WGLEWContext();
			sWGLEWContext.reset(context);
			GLenum status = wglewInit();
			if(status != GLEW_OK)
			{
				printf("FUCK YOUR MOTHER\n");
				// Critical error
			}
			printOpenGLError();
		}
		return sWGLEWContext.get();
	}

	CLAIRE_NAMESPACE_END
}
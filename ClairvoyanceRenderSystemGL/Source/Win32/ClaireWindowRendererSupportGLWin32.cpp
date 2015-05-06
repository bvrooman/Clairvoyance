#include "ClaireWindowRendererSupportGLWin32.h"

#include "ClaireWindowRendererComponentGLWin32.h"
#include "Win32\ClaireWindowPlatformComponentWin32.h"
#include "ClaireRenderWindow.h"
#include "ClaireRenderContextGLWin32.h"
#include "Win32\ClaireDeviceContextWin32.h"

#include "ClaireSTLContainers.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	WindowRendererSupportGLWin32::WindowRendererSupportGLWin32(void)
	{
	}

	WindowRendererSupportGLWin32::~WindowRendererSupportGLWin32(void)
	{
		// Clean up
		mDummyRenderContext->release();

		DestroyWindow(mDummyHWND);
		HINSTANCE hInstance = (HINSTANCE)GetWindowLong(mDummyHWND, GWL_HINSTANCE);
		UnregisterClass(mDummyText, hInstance);
	}

	void WindowRendererSupportGLWin32::initialize(void)
	{
		if(!initializeWGL())
		{
			assert(false && "Unale to initialize WGL");
			return;
		}
	}

	void WindowRendererSupportGLWin32::startDummyContext(void)
	{
		bool success = mDummyRenderContext->makeCurrent();
		assert(success);
	}

	void WindowRendererSupportGLWin32::endDummyContext(void)
	{
		mDummyRenderContext->endCurrent();
	}

	bool WindowRendererSupportGLWin32::initializeWGL(void)
	{
		const uint16_t moduleFlags =
			GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
			GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT;
		LPCWSTR moduleName = L"";
		HINSTANCE hInstance = nullptr;
		GetModuleHandleEx(moduleFlags, moduleName, &hInstance);

		WNDCLASS dummyClass;
		memset(&dummyClass, 0, sizeof(WNDCLASS));
		dummyClass.style = CS_OWNDC;
		dummyClass.hInstance = hInstance;
		dummyClass.lpfnWndProc = DefWindowProc;
		dummyClass.lpszClassName = mDummyText;
		RegisterClass(&dummyClass);

		mDummyHWND = CreateWindow(
			mDummyText,
			mDummyText,
			WS_POPUP | WS_CLIPCHILDREN,
			0, 0, 0, 0,
			0,
			0,
			hInstance,
			0);

		HDC hdc = GetDC(mDummyHWND);

		// assign a simple OpenGL pixel format that everyone supports
		PIXELFORMATDESCRIPTOR pfd;
		memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.cColorBits = 16;
		pfd.cDepthBits = 15;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;

		int format = ChoosePixelFormat(hdc, &pfd);
		if(format != 0)
		{
			SetPixelFormat(hdc, format, &pfd);
		}

		bool success = true;

		DeviceContextWin32 dc(hdc);
		mDummyRenderContext = std::make_unique<RenderContextGLWin32>(&dc);
		success &= mDummyRenderContext->makeCurrent();

		if(success)
		{
			const GLubyte* pVersion = glGetString(GL_VERSION);
			std::cout << pVersion << "\n";
			const GLubyte* pShaderVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
			std::cout << pShaderVersion << "\n";

			wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionsStringARB");
			success &= (wglGetExtensionsStringARB != nullptr);

			if(wglGetExtensionsStringARB)
			{
				hdc = wglGetCurrentDC();
				std::istringstream wglexts(wglGetExtensionsStringARB(hdc));
				std::string ext;
				while (wglexts >> ext)
				{
					if (ext == "WGL_ARB_pixel_format")
						mHasPixelFormatARB = true;
					else if (ext == "WGL_ARB_multisample")
						mHasMultisample = true;
					else if (ext == "WGL_EXT_framebuffer_sRGB")
						mHasHardwareGamma = true;
				}
			}

			wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
			success &= (wglChoosePixelFormatARB != nullptr);

			mDummyRenderContext->endCurrent();
		}

		return success;
	}

	WindowRendererComponentUPtr WindowRendererSupportGLWin32::createWindowRendererComponent(RenderWindow* parentRenderWindow) const
	{
		return std::make_unique<WindowRendererComponentGLWin32>(parentRenderWindow);
	}

	void WindowRendererSupportGLWin32::setPixelFormat(const DeviceContext* deviceContext, const PixelFormat& pixelFormat) const
	{
		HDC hdc = static_cast<const DeviceContextWin32*>(deviceContext)->getHDC();

		ushort colourBits = pixelFormat.getRedBits() + pixelFormat.getGreenBits() + pixelFormat.getBlueBits();
		ushort alphaBits = pixelFormat.getAlphaBits();
		ushort depthBits = 24;
		ushort stencilBits = 8;
		ushort samples = 4;

		PIXELFORMATDESCRIPTOR pfd;
		memset(&pfd, 0, sizeof(pfd));
		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = (BYTE)colourBits;
		pfd.cAlphaBits = (BYTE)alphaBits;
		pfd.cDepthBits = (BYTE)depthBits;
		pfd.cStencilBits = (BYTE)stencilBits;

		int format = 0;

		if(mHasMultisample)
		{
			vector<int> attribList;
			attribList.push_back(WGL_DRAW_TO_WINDOW_ARB);	attribList.push_back(GL_TRUE);
			attribList.push_back(WGL_SUPPORT_OPENGL_ARB);	attribList.push_back(GL_TRUE);
			attribList.push_back(WGL_DOUBLE_BUFFER_ARB);	attribList.push_back(GL_TRUE);
			attribList.push_back(WGL_SAMPLE_BUFFERS_ARB);	attribList.push_back(GL_TRUE);
			attribList.push_back(WGL_ACCELERATION_ARB);		attribList.push_back(WGL_FULL_ACCELERATION_ARB);
			attribList.push_back(WGL_COLOR_BITS_ARB);		attribList.push_back(colourBits);
			attribList.push_back(WGL_ALPHA_BITS_ARB);		attribList.push_back(alphaBits);
			attribList.push_back(WGL_DEPTH_BITS_ARB);		attribList.push_back(depthBits);
			attribList.push_back(WGL_STENCIL_BITS_ARB);		attribList.push_back(stencilBits);
			attribList.push_back(WGL_SAMPLES_ARB);			attribList.push_back(samples);

			if(mHasHardwareGamma)
			{
				attribList.push_back(WGL_FRAMEBUFFER_SRGB_CAPABLE_EXT);	attribList.push_back(GL_TRUE);
			}

			attribList.push_back(0);

			UINT nformats;
			wglChoosePixelFormatARB(hdc, &(attribList[0]), nullptr, 1, &format, &nformats);
		}
		else
		{
			format = ChoosePixelFormat(hdc, &pfd);
		}

		SetPixelFormat(hdc, format, &pfd);
	}

	CLAIRE_NAMESPACE_END
}
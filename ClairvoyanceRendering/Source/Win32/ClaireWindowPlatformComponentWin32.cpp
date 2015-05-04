#include "ClaireWindowPlatformComponentWin32.h"

#include "ClaireRenderWindow.h"

#include "ClaireWindowEvents.h"

#include <string.h>
#include <string>

#include "ClaireDeviceContextWin32.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	WindowPlatformComponentWin32::WindowPlatformComponentWin32(RenderWindow* parentRenderWindow)
		: WindowPlatformComponent(parentRenderWindow)
		, mHWnd(nullptr)
	{
	}

	WindowPlatformComponentWin32::~WindowPlatformComponentWin32(void)
	{
		destroy();
	}

	void WindowPlatformComponentWin32::create(void)
	{
		if (mHWnd)
			destroy();

		const uint16_t moduleFlags =
			GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
			GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT;
		LPCWSTR moduleName = L"";
		HINSTANCE hInstance = nullptr;
		GetModuleHandleEx(moduleFlags, moduleName, &hInstance);

		mColourDepth = getFullscreen() ? 
			mParentRenderWindow->getPixelFormat()->getColourDepth() :
			GetDeviceCaps(GetDC(0), BITSPIXEL);
		int top = -1;
		int left = -1;
		// TODO
		// Get left and top from another optional source
		const size_t width = mParentRenderWindow->getWidth();
		const size_t height = mParentRenderWindow->getHeight();
		string name = mParentRenderWindow->getName();

		// Get the default primary monitor
		POINT windowAnchorPoint;
		windowAnchorPoint.x = left;
		windowAnchorPoint.y = top;
		HMONITOR hMonitor = MonitorFromPoint(windowAnchorPoint, MONITOR_DEFAULTTOPRIMARY);

		// Get the target monitor info
		MONITORINFOEX monitorInfoEx;
		memset(&monitorInfoEx, 0, sizeof(MONITORINFOEX));
		monitorInfoEx.cbSize = sizeof(MONITORINFOEX);
		GetMonitorInfo(hMonitor, &monitorInfoEx);

		size_t deviceNameLength = wcslen(monitorInfoEx.szDevice) + 1;
		char* deviceName = new char[deviceNameLength];
		wcstombs_s(new size_t, deviceName, deviceNameLength, monitorInfoEx.szDevice, deviceNameLength);
		mDeviceName = std::move(deviceName);
		delete[] deviceName;

		mFullscreenWindowStyle = WS_VISIBLE | WS_CLIPCHILDREN | WS_POPUP;
		mWindowedWindowStyle = WS_VISIBLE | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW;
		mWindowedWindowStyle ^= WS_THICKFRAME;

		// If no left or top positions have been specified,
		// centre the window
		if(left == -1 || top == -1)
		{
			size_t windowWidth;
			size_t windowHeight;
			adjustWindow(width, height, windowWidth, windowHeight);

			size_t screenWidth = monitorInfoEx.rcWork.right - monitorInfoEx.rcWork.left;
			size_t screenHeight = monitorInfoEx.rcWork.bottom - monitorInfoEx.rcWork.top;

			if(left == -1)
			{
				left = (int)(monitorInfoEx.rcWork.left + (screenWidth - windowWidth) / 2);
			}
			if(top == -1)
			{
				top = (int)(monitorInfoEx.rcWork.top + (screenHeight - windowHeight) / 2);
			}
		}
		mLeft = left;
		mTop = top;

		DWORD dwStyleEx = 0;

		if(getFullscreen())
		{
			dwStyleEx |= WS_EX_TOPMOST;
			mLeft = monitorInfoEx.rcWork.left;
			mTop = monitorInfoEx.rcWork.top;
		}
		else
		{
			dwStyleEx |= WS_EX_APPWINDOW;
		}

		WNDCLASS wc;
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = WindowEvents::wndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = L"ClairvoyanceWindow";
		RegisterClass(&wc);

		if(getFullscreen())
		{
			DEVMODE dmScreenSettings;
			memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
			dmScreenSettings.dmSize = sizeof(dmScreenSettings);
			dmScreenSettings.dmPelsWidth = (DWORD)width;
			dmScreenSettings.dmPelsHeight = (DWORD)height;
			dmScreenSettings.dmBitsPerPel = (DWORD)mColourDepth;
			dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
			{
				// Critical Error
			}
		}

		size_t windowNameLen = strlen(name.c_str()) + 1;
		wchar_t* windowName = new wchar_t[windowNameLen];
		mbstowcs_s(new size_t, windowName, windowNameLen, name.c_str(), windowNameLen);

		mHWnd = CreateWindowEx(
			dwStyleEx,
			L"ClairvoyanceWindow",
			windowName,
			getWindowStyle(getFullscreen()),
			(int)mLeft,
			(int)mTop,
			(int)width,
			(int)height,
			nullptr,
			nullptr,
			hInstance,
			this
			);

		delete windowName;

		HDC hdc = GetDC(mHWnd);
		mDeviceContext = std::make_unique<DeviceContextWin32>(hdc);
	}

	void WindowPlatformComponentWin32::destroy(void)
	{
		if(!mHWnd)
			return;

		if(getFullscreen())
		{
			ChangeDisplaySettingsEx((LPCWSTR)mDeviceName.c_str(), nullptr, nullptr, 0, nullptr);
		}
		DestroyWindow(mHWnd);

		mHWnd = nullptr;
		mDeviceName = "";
	}

	void WindowPlatformComponentWin32::swapBuffers(void)
	{
		DeviceContextWin32* dc = static_cast<DeviceContextWin32*>(mDeviceContext.get());
		HDC hdc = dc->getHDC();
		SwapBuffers(hdc);
	}

	void WindowPlatformComponentWin32::adjustWindow(
		size_t clientWidth, size_t clientHeight,
		size_t& outWindowWidth, size_t& outWindowHeight)
	{
		RECT rc;
		SetRect(&rc, 0, 0, (int)clientWidth, (int)clientHeight);
		AdjustWindowRect(&rc, getWindowStyle(getFullscreen()), false);
		outWindowWidth = rc.right - rc.left;
		outWindowHeight = rc.bottom - rc.top;

		HMONITOR hMonitor = MonitorFromWindow(mHWnd, MONITOR_DEFAULTTONEAREST);
		MONITORINFOEX monitorInfoEx;
		memset(&monitorInfoEx, 0, sizeof(MONITORINFOEX));
		monitorInfoEx.cbSize = sizeof(MONITORINFOEX);
		GetMonitorInfo(hMonitor, &monitorInfoEx);

		LONG maxWidth = monitorInfoEx.rcWork.right - monitorInfoEx.rcWork.left;
		LONG maxHeight = monitorInfoEx.rcWork.top - monitorInfoEx.rcWork.bottom;
		outWindowWidth = std::min(outWindowWidth, (size_t)maxWidth);
		outWindowHeight = std::min(outWindowHeight, (size_t)maxHeight);
	}

	CLAIRE_NAMESPACE_END
}
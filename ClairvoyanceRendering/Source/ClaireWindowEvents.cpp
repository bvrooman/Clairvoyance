#include "ClaireWindowEvents.h"
#include "ClaireRenderWindow.h"
#include "ClaireWindowPlatformComponent.h"
#include "ClaireRenderSystem.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

		void WindowEvents::messageHandler(void)
	{
#if CLAIRE_PLATFORM == CLAIRE_PLATFORM_WIN32
		MSG msg;
		while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
#endif
	}

#if CLAIRE_PLATFORM == CLAIRE_PLATFORM_WIN32
	LRESULT CALLBACK WindowEvents::wndProc(
		HWND hWnd,
		UINT msg,
		WPARAM wParam, LPARAM lParam)
	{
		RenderWindow* window = nullptr;

		if(msg == WM_CREATE)
		{
			LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
			WindowPlatformComponent* component = (WindowPlatformComponent*)lpcs->lpCreateParams;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)component);
			window = component->getParentRenderWindow();
			return 0;
		}
		else
		{
			WindowPlatformComponent* component = (WindowPlatformComponent*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if(component)
			{
				window = component->getParentRenderWindow();
			}
		}

		if(!window)
		{
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}

		switch (msg)
		{

		case WM_ACTIVATE:
		{
			bool active = (LOWORD(wParam) != WA_INACTIVE);
			if (active)
			{
				//window->setActive(true);
			}
			else
			{
				//window->setActive(false);
			}
			break;
		}

		case WM_SYSKEYDOWN:
			switch (wParam)
			{
			case VK_CONTROL:
			case VK_SHIFT:
			case VK_MENU:
				return 0;
			}
			break;

		case WM_SYSKEYUP:
			switch (wParam)
			{
			case VK_CONTROL:
			case VK_SHIFT:
			case VK_MENU:
			case VK_F10:
				return 0;
			}
			break;

		case WM_SYSCOMMAND:
		{
			switch (wParam)
			{
			case SC_SCREENSAVE:
			case SC_MONITORPOWER:
				return 0;
			}
			break;
		}

		case WM_SYSCHAR:
			if (wParam != VK_SPACE)
				return 0;
			break;
		case WM_ENTERSIZEMOVE:
			break;
		case WM_EXITSIZEMOVE:
			break;
		case WM_MOVE:
			//window->windowMovedOrResized();
			break;
		case WM_DISPLAYCHANGE:
			break;
		case WM_SIZE:
			window->notifyOnResize();
			//window->windowMovedOrResized();
			break;
		case WM_GETMINMAXINFO:
			break;
		case WM_CLOSE:
		{
			window->notifyOnClose();
			window->getManager()->destroyRenderWindow(window->getName());
			PostQuitMessage(0);
			return 0;
		}

		}

		// Pass All Unhandled Messages To DefWindowProc
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
#endif

	CLAIRE_NAMESPACE_END
}
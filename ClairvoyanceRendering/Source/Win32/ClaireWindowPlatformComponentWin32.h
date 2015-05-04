#ifndef CLAIRE_WINDOW_COMPONENT_WIN32_H
#define CLAIRE_WINDOW_COMPONENT_WIN32_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireWindowPlatformComponent.h"

#define NOMINMAX
#include <Windows.h>

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_RENDERING_EXPORT WindowPlatformComponentWin32
		: public WindowPlatformComponent
	{
	public:
		WindowPlatformComponentWin32(RenderWindow* renderWindow);
		~WindowPlatformComponentWin32(void);

		void create(void) CLAIRE_OVERRIDE;
		void destroy(void) CLAIRE_OVERRIDE;

		void swapBuffers(void) CLAIRE_OVERRIDE;

		void adjustWindow(
			size_t clientWidth, size_t clientHeight,
			size_t& outWindowWidth, size_t& outWindowHeight);

	protected:
		DWORD getWindowStyle(bool fullscreen)
		{
			if(fullscreen)
				return getFullscreenWindowStyle();
			else
				return getWindowedWindowStyle();
		}
		DWORD getFullscreenWindowStyle(void) { return mFullscreenWindowStyle; }
		DWORD getWindowedWindowStyle(void) { return mWindowedWindowStyle; }

	protected:
		HWND mHWnd;

		DWORD mFullscreenWindowStyle;
		DWORD mWindowedWindowStyle;
	};

	CLAIRE_NAMESPACE_END
}

#endif
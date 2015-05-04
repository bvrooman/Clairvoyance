#ifndef CLAIRE_WINDOW_EVENTS_H
#define CLAIRE_WINDOW_EVENTS_H

#include "ClaireRenderingPrerequisites.h"

#if CLAIRE_PLATFORM == CLAIRE_PLATFORM_WIN32
#	define NOMINMAX
#	include <Windows.h>
#endif

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_RENDERING_EXPORT WindowEvents
	{
	public:
		static void	messageHandler(void);

#if CLAIRE_PLATFORM == CLAIRE_PLATFORM_WIN32
		// Internal wndProc (RenderWindows use this when creating a Win32 window)
		static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif
	};

	CLAIRE_NAMESPACE_END
}

#endif
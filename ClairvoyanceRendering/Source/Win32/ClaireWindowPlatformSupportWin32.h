#ifndef CLAIRE_PLATFORM_SUPPORT_WIN32_H
#define CLAIRE_WINDOW_PLATFORM_SUPPORT_WIN32_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireWindowPlatformSupport.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_RENDERING_EXPORT WindowPlatformSupportWin32
		: public WindowPlatformSupport
	{
	public:
		WindowPlatformSupportWin32(void) = default;
		~WindowPlatformSupportWin32(void) = default;

		WindowPlatformComponentUPtr createWindowPlaformComponent(RenderWindow* parentRenderWindow) const CLAIRE_OVERRIDE;
	};

	CLAIRE_NAMESPACE_END
}

#endif
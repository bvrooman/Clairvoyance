#include "ClaireWindowPlatformSupportWin32.h"

#include "ClaireWindowPlatformComponentWin32.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)
	
	WindowPlatformComponentUPtr WindowPlatformSupportWin32::createWindowPlaformComponent(RenderWindow* parentRenderWindow) const
	{
		return std::make_unique<WindowPlatformComponentWin32>(parentRenderWindow);
	}

	CLAIRE_NAMESPACE_END
}

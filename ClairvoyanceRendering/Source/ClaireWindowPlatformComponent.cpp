#include "ClaireWindowPlatformComponent.h"

#include "ClaireRenderWindow.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)
	
	WindowPlatformComponent::WindowPlatformComponent(RenderWindow* parentRenderWindow)
		: mParentRenderWindow(parentRenderWindow)
	{
	}

	bool WindowPlatformComponent::getFullscreen(void)
	{
		return mParentRenderWindow->getFullscreen();
	}

	CLAIRE_NAMESPACE_END
}
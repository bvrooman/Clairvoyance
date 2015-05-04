#include "ClaireWindowPlatformComponent.h"

#include "ClaireRenderWindow.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)
	
	WindowPlatformComponent::WindowPlatformComponent(RenderWindow* parentRenderWindow)
		: mParentRenderWindow(parentRenderWindow)
		, mDeviceName("")
		, mLeft(0)
		, mTop(0)
		, mColourDepth(0)
	{
	}

	WindowPlatformComponent::~WindowPlatformComponent(void)
	{
	}

	bool WindowPlatformComponent::getFullscreen(void)
	{
		return mParentRenderWindow->getFullscreen();
	}

	CLAIRE_NAMESPACE_END
}
#include "ClaireWindowRendererComponent.h"

#include "ClaireRenderWindow.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	WindowRendererComponent::WindowRendererComponent(RenderWindow* parentRenderWindow)
		: mParentRenderWindow(parentRenderWindow)
	{
	}

	WindowRendererComponent::~WindowRendererComponent(void)
	{
	}

	CLAIRE_NAMESPACE_END
}
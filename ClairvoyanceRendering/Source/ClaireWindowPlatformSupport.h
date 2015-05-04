#ifndef CLAIRE_WINDOW_PLATFORM_SUPPORT_H
#define CLAIRE_WINDOW_PLATFORM_SUPPORT_H

#include "ClaireRenderingPrerequisites.h"
#include "Memory\ClaireMemoryConfig.h"

#include "ClaireWindowPlatformComponent.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class RenderSystem;
	
	class CLAIRE_RENDERING_EXPORT WindowPlatformSupport
		//: public GeneralAllocatedObject
	{
	public:
		WindowPlatformSupport(void) {}
		virtual ~WindowPlatformSupport(void) {}

		virtual WindowPlatformComponentUPtr createWindowPlaformComponent(RenderWindow* parentRenderWindow) const CLAIRE_ABSTRACT;
	};

	typedef std::unique_ptr<WindowPlatformSupport> WindowPlatformSupportUPtr;

	CLAIRE_NAMESPACE_END
}

#endif
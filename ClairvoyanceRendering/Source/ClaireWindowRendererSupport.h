#ifndef CLAIRE_RENDERER_SUPPORT_H
#define CLAIRE_RENDERER_SUPPORT_H

#include "ClaireRenderingPrerequisites.h"
#include "Memory\ClaireMemoryConfig.h"

#include "ClaireWindowRendererComponent.h"

#include "ClairePixelFormat.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class RenderSystem;
	class RenderWindow;
	class DeviceContext;

	class CLAIRE_RENDERING_EXPORT WindowRendererSupport
		//: public GeneralAllocatedObject
	{
	public:
		WindowRendererSupport(void);
		virtual ~WindowRendererSupport(void);

		virtual void initialize(void) CLAIRE_ABSTRACT;

		virtual WindowRendererComponentUPtr createWindowRendererComponent(RenderWindow* parentRenderWindow) const CLAIRE_ABSTRACT;
		virtual void setPixelFormat(const DeviceContext* deviceContext, const PixelFormat& pixelFormat) const CLAIRE_ABSTRACT;
	};

	typedef std::unique_ptr<WindowRendererSupport> WindowRendererSupportUPtr;
	
	CLAIRE_NAMESPACE_END
}

#endif
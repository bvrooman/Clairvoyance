#ifndef CLAIRE_WINDOW_RENDERER_COMPONENT_H
#define CLAIRE_WINDOW_RENDERER_COMPONENT_H

#include "ClaireRenderingPrerequisites.h"
#include "Memory\ClaireMemoryConfig.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class RenderWindow;

	class CLAIRE_RENDERING_EXPORT WindowRendererComponent
		//: public GeneralAllocatedObject
	{
	public:
		WindowRendererComponent(RenderWindow* parentRenderWindow);
		virtual ~WindowRendererComponent(void) = default;

		RenderWindow* getParentRenderWindow(void) const { return mParentRenderWindow; }

		virtual void create(void) CLAIRE_ABSTRACT;
		virtual void destroy(void) CLAIRE_ABSTRACT;

	protected:
		RenderWindow* mParentRenderWindow;
	};

	typedef std::unique_ptr<WindowRendererComponent> WindowRendererComponentUPtr;

	CLAIRE_NAMESPACE_END
}

#endif
#ifndef CLAIRE_RENDER_WINDOW_EVENT
#define CLAIRE_RENDER_WINDOW_EVENT

#include "ClaireRenderingPrerequisites.h"
#include "Memory\ClaireMemoryConfig.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class RenderWindow;

	class CLAIRE_RENDERING_EXPORT RenderWindowEvent
		//: public GeneralAllocatedObject
	{
	public:
		RenderWindowEvent(RenderWindow* window)
			: mRenderWindow(window)
		{}
		~RenderWindowEvent(void)
		{}

		RenderWindow* getRenderWindow(void) const { return mRenderWindow; }

	private:
		RenderWindow* mRenderWindow;
	};

	CLAIRE_NAMESPACE_END
}

#endif
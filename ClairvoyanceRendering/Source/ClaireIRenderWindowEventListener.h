#ifndef CLAIRE_I_RENDER_WINDOW_EVENT_LISTENER_H
#define CLAIRE_I_RENDER_WINDOW_EVENT_LISTENER_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireRenderWindowEvent.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_RENDERING_EXPORT IRenderWindowEventListener
	{
	public:
		virtual void onWindowMove(const RenderWindowEvent& event) CLAIRE_ABSTRACT;
		virtual void onWindowResize(const RenderWindowEvent& event) CLAIRE_ABSTRACT;
		virtual void onWindowClose(const RenderWindowEvent& event) CLAIRE_ABSTRACT;
	};

	CLAIRE_NAMESPACE_END
}

#endif
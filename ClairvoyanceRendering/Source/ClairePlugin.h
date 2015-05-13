#ifndef CLAIRE_PLUGIN_H
#define CLAIRE_PLUGIN_H

#include "ClaireRenderingPrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class RenderRoot;

	class CLAIRE_RENDERING_EXPORT Plugin
	{
	public:
		Plugin(void) = default;
		virtual ~Plugin(void) = default;

		virtual void install(RenderRoot* renderRoot) CLAIRE_ABSTRACT;
		virtual void uninstall(RenderRoot* renderRoot) CLAIRE_ABSTRACT;
	};

	CLAIRE_NAMESPACE_END
}

#endif
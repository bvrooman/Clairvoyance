#ifndef CLAIRE_FLAT_NODE_H
#define CLAIRE_FLAT_NODE_H

#include "ClaireRenderingPrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_RENDERING_EXPORT FlatNode
	{
	public:
		FlatNode(void)
		{}

		NodeHandle parentHandle = 0;
		size_t numChildren = 0;
	};

	CLAIRE_NAMESPACE_END
}

#endif
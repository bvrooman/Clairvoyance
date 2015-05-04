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
			: parentHandle(0)
			, numChildren(0)
		{}

		NodeHandle parentHandle;
		size_t numChildren;
	};

	CLAIRE_NAMESPACE_END
}

#endif
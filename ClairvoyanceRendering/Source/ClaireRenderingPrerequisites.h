#ifndef CLAIRE_RENDERING_PREREQUISITES_H
#define CLAIRE_RENDERING_PREREQUISITES_H

#include "ClairePrerequisites.h"
#include "Platform\ClairePlatform.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	typedef unsigned int EnumFlags;
	typedef ushort NodeHandle;

	const size_t MAX_NODE_CHAIN_SIZE = 1024;

	CLAIRE_NAMESPACE_END
}

#endif
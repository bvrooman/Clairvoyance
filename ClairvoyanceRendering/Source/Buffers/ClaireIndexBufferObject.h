#ifndef CLAIRE_INDEX_BUFFER_OBJECT_H
#define CLAIRE_INDEX_BUFFER_OBJECT_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireBufferObject.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_RENDERING_EXPORT IndexBufferObject
		: public BufferObject
	{
	public:
		enum IndexType
		{
			IT_8BIT,
			IT_16BIT,
			IT_32BIT
		};

	public:
		IndexBufferObject(BufferObjectManager* manager, IndexType indexType, size_t numIndices, EnumFlags usageSettings);
		virtual ~IndexBufferObject(void);

	protected:
		IndexType mIndexType;
		size_t mIndexSize;
		size_t mNumIndices;
	};

	CLAIRE_NAMESPACE_END
}

#endif
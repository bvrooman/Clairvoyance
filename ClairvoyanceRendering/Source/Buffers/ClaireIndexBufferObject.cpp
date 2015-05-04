#include "ClaireIndexBufferObject.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	IndexBufferObject::IndexBufferObject(BufferObjectManager* manager, IndexType indexType, size_t numIndices, EnumFlags usageSettings)
		: BufferObject(manager, usageSettings)
		, mIndexType(indexType)
		, mNumIndices(numIndices)
	{
		switch(mIndexType)
		{
		case IT_8BIT:
			mIndexSize = sizeof(uint8_t);
			break;

		case IT_16BIT:
			mIndexSize = sizeof(uint16_t);
			break;

		case IT_32BIT:
		default:
			mIndexSize = sizeof(uint32_t);
			break;
		}
		mBytes = mIndexSize * mNumIndices;
	}

	IndexBufferObject::~IndexBufferObject(void)
	{

	}

	CLAIRE_NAMESPACE_END
}
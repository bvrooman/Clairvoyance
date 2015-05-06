#include "ClaireVertexBufferObject.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	VertexBufferObject::VertexBufferObject(BufferObjectManager* manager, size_t vertexSize, size_t numVertices, EnumFlags usageSettings)
		: BufferObject(manager, usageSettings)
		, mVertexSize(vertexSize)
		, mNumVertices(numVertices)
	{
		mBytes = mVertexSize * mNumVertices;
	}

	VertexBufferObject::~VertexBufferObject(void)
	{
	}

	CLAIRE_NAMESPACE_END
}
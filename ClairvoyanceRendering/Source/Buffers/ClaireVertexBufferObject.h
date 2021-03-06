#ifndef CLAIRE_VERTEX_BUFFER_OBJECT_H
#define CLAIRE_VERTEX_BUFFER_OBJECT_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireBufferObject.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_RENDERING_EXPORT VertexBufferObject
		: public BufferObject
	{
	public:
		VertexBufferObject(BufferObjectManager* manager, size_t vertexSize, size_t numVertices, EnumFlags usageSettings);
		virtual ~VertexBufferObject(void) = default;

		size_t getVertexSize(void) const { return mVertexSize; }
		size_t getNumVertices(void) const { return mNumVertices; }

	protected:
		size_t mVertexSize = 0;
		size_t mNumVertices = 0;
	};

	CLAIRE_NAMESPACE_END
}

#endif
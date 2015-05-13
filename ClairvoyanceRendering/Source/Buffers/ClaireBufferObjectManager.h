#ifndef CLAIRE_BUFFER_OBJECT_MANAGER_H
#define CLAIRE_BUFFER_OBJECT_MANAGER_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireSTLContainers.h"
#include "ClaireBufferObject.h"
#include "ClaireIndexBufferObject.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_RENDERING_EXPORT BufferObjectManager
	{
		CLAIRE_MOVABLE_ONLY(BufferObjectManager)

	public:
		BufferObjectManager(void) = default;
		virtual ~BufferObjectManager(void) = default;

		// Index Buffer Object
		virtual BufferObject* createIndexBufferObject(IndexBufferObject::IndexType indexType, size_t numIndices, EnumFlags usageSettings) CLAIRE_ABSTRACT;

		// Vertex Buffer Object
		virtual BufferObject* createVertexBufferObject(size_t vertexSize, size_t numVertices, EnumFlags usageSettings) CLAIRE_ABSTRACT;

	protected:
		typedef list<BufferObjectUPtr> BufferObjectList;
		BufferObjectList mBufferObjectList;
	};

	typedef std::unique_ptr<BufferObjectManager> BufferObectManagerUPtr;

	CLAIRE_NAMESPACE_END
}

#endif
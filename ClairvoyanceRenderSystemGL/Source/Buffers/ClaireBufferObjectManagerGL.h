#ifndef CLAIRE_BUFFER_OBJECT_MANAGER_GL_H
#define CLAIRE_BUFFER_OBJECT_MANAGER_GL_H

#include "ClaireGLPrerequisites.h"

#include "Buffers\ClaireBufferObjectManager.h"

#include "Memory\ClaireMemoryConfig.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_GL_EXPORT BufferObjectManagerGL
		: public BufferObjectManager
	{
	public:
		BufferObjectManagerGL(void);
		~BufferObjectManagerGL(void) = default;

		void* allocateScratch(size_t size);
		void deallocateScratch(void* ptr);

		BufferObject* createIndexBufferObject(IndexBufferObject::IndexType indexType, size_t numIndices, EnumFlags usageSettings);
		BufferObject* createVertexBufferObject(size_t vertexSize, size_t numVertices, EnumFlags usageSettings);

		GLenum getGLBufferUsage(EnumFlags lockSettings);

	private:
		HeapArea mHeapArea;
		MemoryArenaPool mMemoryArena;
	};

	CLAIRE_NAMESPACE_END
}

#endif
#include "ClaireBufferObjectManagerGL.h"

#include "ClaireVertexBufferObjectGL.h"
#include "ClaireIndexBufferObjectGL.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	BufferObjectManagerGL::BufferObjectManagerGL(void)
		: mHeapArea(1024 * 1024 * 8)
		, mMemoryArena(mHeapArea.getStart(), mHeapArea.getEnd())
	{

	}

	BufferObjectManagerGL::~BufferObjectManagerGL(void)
	{

	}

	void* BufferObjectManagerGL::allocateScratch(size_t size)
	{
		return mMemoryArena.allocate(size, 32, 0);
	}

	void BufferObjectManagerGL::deallocateScratch(void* ptr)
	{
		mMemoryArena.deallocate(ptr);
	}

	BufferObject* BufferObjectManagerGL::createIndexBufferObject(IndexBufferObject::IndexType indexType, size_t numIndices, EnumFlags usageSettings)
	{
		auto bufferObject = std::make_unique<IndexBufferObjectGL>(this, indexType, numIndices, usageSettings);
		BufferObject* bufferObject_ = bufferObject.get();
		mBufferObjectList.push_back(std::move(bufferObject));
		return bufferObject_;
	}

	BufferObject* BufferObjectManagerGL::createVertexBufferObject(size_t vertexSize, size_t numVertices, EnumFlags usageSettings)
	{
		auto bufferObject = std::make_unique<VertexBufferObjectGL>(this, vertexSize, numVertices, usageSettings);
		BufferObject* bufferObject_ = bufferObject.get();
		mBufferObjectList.push_back(std::move(bufferObject));
		return bufferObject_;
	}

	GLenum BufferObjectManagerGL::getGLBufferUsage(EnumFlags lockSettings)
	{
		if(lockSettings & BufferObject::US_DYNAMIC)
		{
			return GL_DYNAMIC_DRAW;
		}
		else
		{
			return GL_STATIC_DRAW;
		}
	}

	CLAIRE_NAMESPACE_END
}
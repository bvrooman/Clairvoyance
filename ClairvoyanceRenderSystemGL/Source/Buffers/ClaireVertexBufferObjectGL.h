#ifndef CLAIRE_VERTEX_BUFFER_OBJECT_GL_H
#define CLAIRE_VERTEX_BUFFER_OBJECT_GL_H

#include "ClaireGLPrerequisites.h"

#include "Buffers\ClaireVertexBufferObject.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_GL_EXPORT VertexBufferObjectGL
		: public VertexBufferObject
	{
	public:
		VertexBufferObjectGL(BufferObjectManager* manager, size_t vertexSize, size_t numVertices, EnumFlags usageSettings);
		~VertexBufferObjectGL(void);

	protected:
		void* lock_(size_t offset, size_t length, EnumFlags lockSettings);
		void unlock_(void);

		void readData(size_t offset, size_t length, void* pDest);
		void writeData(size_t offset, size_t length, const void* pSrc, bool discardWholeBuffer);

	private:
		size_t mScratchOffset = 0;
		size_t mScratchLength = 0;
		void* mScratchPtr = nullptr;
		bool mLockedToScratch = false;

		GLenum mBufferTarget;
		GLuint mBufferID;
	};

	CLAIRE_NAMESPACE_END
}

#endif
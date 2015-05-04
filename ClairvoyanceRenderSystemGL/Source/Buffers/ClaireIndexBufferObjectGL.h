#ifndef CLAIRE_INDEX_BUFFER_OBJECT_GL_H
#define CLAIRE_INDEX_BUFFER_OBJECT_GL_H

#include "ClaireGLPrerequisites.h"

#include "Buffers\ClaireIndexBufferObject.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_GL_EXPORT IndexBufferObjectGL
		: public IndexBufferObject
	{
	public:
		IndexBufferObjectGL(BufferObjectManager* manager, IndexType indexType, size_t numIndices, EnumFlags usageSettings);
		~IndexBufferObjectGL(void);

		GLuint getBufferID(void) const { return mBufferID; }

	protected:
		void* lock_(size_t offset, size_t length, EnumFlags lockSettings);
		void unlock_(void);

		void readData(size_t offset, size_t length, void* pDest);
		void writeData(size_t offset, size_t length, const void* pSrc, bool discardWholeBuffer);

	private:
		size_t mScratchOffset;
		size_t mScratchLength;
		void* mScratchPtr;
		bool mLockedToScratch;

		GLenum mBufferTarget;
		GLuint mBufferID;
	};

	CLAIRE_NAMESPACE_END
}

#endif
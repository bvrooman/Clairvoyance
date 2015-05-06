#include "ClaireVertexBufferObjectGL.h"

#include "Buffers\ClaireBufferObjectManagerGL.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	VertexBufferObjectGL::VertexBufferObjectGL(BufferObjectManager* manager, size_t vertexSize, size_t numVertices, EnumFlags usageSettings)
		: VertexBufferObject(manager, vertexSize, numVertices, usageSettings)
	{
		mBufferTarget = GL_ARRAY_BUFFER;

		glGenBuffers(1, &mBufferID);
		glBindBuffer(mBufferTarget, mBufferID);
	}

	VertexBufferObjectGL::~VertexBufferObjectGL(void)
	{
		glDeleteBuffers(1, &mBufferID);
	}

	void* VertexBufferObjectGL::lock_(size_t offset, size_t length, EnumFlags lockSettings)
	{
		void* buffer = ((BufferObjectManagerGL*)mManager)->allocateScratch(length);

		if(buffer)
		{
			mLockedToScratch = true;
			mScratchPtr = buffer;
			mScratchOffset = offset;
			mScratchLength = length;

			if(!(lockSettings & LS_DISCARD) && lockSettings & LS_READ)
			{
				readData(mScratchOffset, mScratchLength, buffer);
			}
		}

		return buffer;
	}
	void VertexBufferObjectGL::unlock_(void)
	{
		if(mLockedToScratch)
		{
			if(mLockSettings & LS_WRITE)
			{
				bool discardWholeBuffer = mScratchOffset == 0 && mScratchLength == mBytes;
				writeData(mScratchOffset, mScratchLength, mScratchPtr, discardWholeBuffer);
			}

			((BufferObjectManagerGL*)mManager)->deallocateScratch(mScratchPtr);
			mLockedToScratch = false;
		}
	}

	void VertexBufferObjectGL::readData(size_t offset, size_t length, void* pDest)
	{
		glBindBuffer(mBufferTarget, mBufferID);
		glGetBufferSubData(mBufferTarget, offset, length, pDest);
	}
	void VertexBufferObjectGL::writeData(size_t offset, size_t length, const void* pSrc, bool discardWholeBuffer)
	{
		GLenum usage = ((BufferObjectManagerGL*)mManager)->getGLBufferUsage(mUsageSettingsFlags);
		if(offset == 0 && length == mBytes)
		{
			glBufferData(mBufferTarget, mBytes, pSrc, usage);
		}
		else
		{
			if(discardWholeBuffer)
			{
				// Create the data store with uninitialized data
				glBufferData(mBufferTarget, mBytes, nullptr, usage);
			}
			glBufferSubData(mBufferTarget, offset, length, pSrc);
		}
	}

	CLAIRE_NAMESPACE_END
}
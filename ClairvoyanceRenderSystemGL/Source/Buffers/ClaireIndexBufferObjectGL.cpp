#include "ClaireIndexBufferObjectGL.h"

#include "ClaireBufferObjectManagerGL.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	IndexBufferObjectGL::IndexBufferObjectGL(BufferObjectManager* manager, IndexType indexType, size_t numIndices, EnumFlags usageSettings)
		: IndexBufferObject(manager, indexType, numIndices, usageSettings)
		, mScratchOffset(0)
		, mScratchLength(0)
		, mScratchPtr(nullptr)
		, mLockedToScratch(false)
	{
		mBufferTarget = GL_ELEMENT_ARRAY_BUFFER;

		glGenBuffers(1, &mBufferID);
		glBindBuffer(mBufferTarget, mBufferID);
	}

	IndexBufferObjectGL::~IndexBufferObjectGL(void)
	{
		glDeleteBuffers(1, &mBufferID);
	}

	void* IndexBufferObjectGL::lock_(size_t offset, size_t length, EnumFlags lockSettings)
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

	void IndexBufferObjectGL::unlock_(void)
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

	void IndexBufferObjectGL::readData(size_t offset, size_t length, void* pDest)
	{
		glBindBuffer(mBufferTarget, mBufferID);
		glGetBufferSubData(mBufferTarget, offset, length, pDest);
	}

	void IndexBufferObjectGL::writeData(size_t offset, size_t length, const void* pSrc, bool discardWholeBuffer)
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
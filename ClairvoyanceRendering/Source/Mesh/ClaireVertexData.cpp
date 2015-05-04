#include "ClaireVertexData.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	VertexData::VertexData(void)
		: mCurrentHandle(0)
	{

	}

	VertexData::~VertexData(void)
	{

	}

	VertexData::VertexBufferObjectHandle VertexData::addVertexBufferFormat(VertexBufferFormatUPtr format)
	{
		VertexBufferObjectHandle handle = mCurrentHandle;
		bindVertexBufferFormat(handle, std::move(format));
		mVBOHandleList.push_back(handle);
		mCurrentHandle++;
		return handle;
	}

	void VertexData::bindVertexBuffer(VertexBufferObjectHandle handle, VertexBufferObject* vbo)
	{
		mVertexBufferObjectMap[handle] = vbo;
	}

	void VertexData::bindVertexBufferFormat(VertexBufferObjectHandle handle, VertexBufferFormatUPtr format)
	{
		mVertexBufferFormatMap[handle] = std::move(format);
	}

	VertexBufferFormat* VertexData::getVertexBufferFormat(VertexBufferObjectHandle handle) const
	{
		VertexBufferFormatMap::const_iterator it = mVertexBufferFormatMap.find(handle);
		if(it != mVertexBufferFormatMap.end())
		{
			return it->second.get();
		}
		return nullptr;
	}

	VertexBufferObject* VertexData::getVertexBufferObject(VertexBufferObjectHandle handle) const
	{
		VertexBufferObjectMap::const_iterator it = mVertexBufferObjectMap.find(handle);
		if(it != mVertexBufferObjectMap.end())
		{
			return it->second;
		}
		return nullptr;
	}

	VertexData::VertexBufferObjectHandle VertexData::getVBOHandleFromSemantic(IndexedVertexAttributeSemantic semantic)
	{
		VertexBufferObjectHandle ret = INVALID_HANDLE;
		for_each(mVBOHandleList.begin(), mVBOHandleList.end(), [&](VertexBufferObjectHandle handle)
		{
			VertexBufferFormat* format = getVertexBufferFormat(handle);
			if(format)
			{
				if (format->getVertexFormatPiece().hasSemantic(semantic))
				{
					ret = handle;
				}
			}
		});
		return ret;
	}

	CLAIRE_NAMESPACE_END
}
#include "ClaireVertexDataFormat.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	VertexDataFormat::VertexDataFormat(void)
	: mNumVertexBufferFormats(0)
	{
	}

	VertexDataFormat::~VertexDataFormat(void)
	{
	}

	VertexBufferFormat& VertexDataFormat::createVertexBufferFormat(VertexBufferFormat::SequenceType sequenceType)
	{
		mVertexBufferFormats[mNumVertexBufferFormats] = new VertexBufferFormat(sequenceType);
		mNumVertexBufferFormats++;
		return *mVertexBufferFormats[mNumVertexBufferFormats - 1];
	}

	VertexBufferFormat* VertexDataFormat::getVertexBufferFormatForSemantic(IndexedVertexAttributeSemantic semantic) const
	{
		if(!mVertexFormat.hasSemantic(semantic))
		{
			return nullptr;
		}

		for(auto&& bufferFormat : range(mVertexBufferFormats, 0, mNumVertexBufferFormats))
		{
			VertexBufferFormat::VertexAttributeVector attributes = bufferFormat->getVertexAttributeVector();
			for(auto&& attribute : attributes)
			{
				if(attribute.getSemantic() == semantic)
				{
					return bufferFormat;
				}
			}
		}
		return nullptr;
	}

	const VertexBufferFormat* const* VertexDataFormat::getVertexBufferFormats(void) const
	{
		return mVertexBufferFormats.data();
	}

	size_t VertexDataFormat::getNumVertexBufferFormats(void) const
	{
		return mNumVertexBufferFormats;
	}

	CLAIRE_NAMESPACE_END
}
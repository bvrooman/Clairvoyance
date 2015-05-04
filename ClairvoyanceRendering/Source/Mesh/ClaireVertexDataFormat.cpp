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

		VertexBufferFormat* formatForSemantic = nullptr;
		for (size_t i = 0; i < mNumVertexBufferFormats; i ++)
		{
			VertexBufferFormat* bufferFormat = mVertexBufferFormats[i];
			VertexBufferFormat::VertexAttributeVector attributes = bufferFormat->getVertexAttributeVector();
			for_each(attributes.begin(), attributes.end(), [&](VertexAttribute attribute)
			{
				if(attribute.getSemantic() == semantic)
				{
					formatForSemantic = bufferFormat;
				}
			});
		}
		return formatForSemantic;
	}

	const VertexBufferFormat* const* VertexDataFormat::getVertexBufferFormats(void) const
	{
		return mVertexBufferFormats.data();
	}


	CLAIRE_NAMESPACE_END
}
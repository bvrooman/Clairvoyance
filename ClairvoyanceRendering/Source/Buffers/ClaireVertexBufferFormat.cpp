#include "ClaireVertexBufferFormat.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	VertexBufferFormat::VertexBufferFormat(SequenceType sequence)
		: mSequenceType(sequence)
	{

	}

	VertexBufferFormat::~VertexBufferFormat(void)
	{

	}

	void VertexBufferFormat::addVertexAttribute(VertexAttribute vertexAttribute)
	{
		mVertexAttributeVector.push_back(vertexAttribute);
		mVertexFormatPiece.addVertexAttribute(vertexAttribute);
	}

	const VertexAttribute* VertexBufferFormat::getVertexAttributeFromSemantic(IndexedVertexAttributeSemantic semantic) const
	{
		const VertexAttribute* ret = nullptr;
		for (
			VertexAttributeVector::const_iterator it = mVertexAttributeVector.begin();
			it != mVertexAttributeVector.end();
		it++
			)
		{
			const VertexAttribute* attribute = &(*it);
			if (attribute->getSemantic() == semantic)
			{
				ret = attribute;
			}
		}
		return ret;
	}

	CLAIRE_NAMESPACE_END
}
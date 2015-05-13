#include "ClaireVertexBufferFormat.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	VertexBufferFormat::VertexBufferFormat(SequenceType sequence)
		: mSequenceType(sequence)
	{

	}

	void VertexBufferFormat::addVertexAttribute(VertexAttribute vertexAttribute)
	{
		mVertexAttributeVector.push_back(vertexAttribute);
		mVertexFormatPiece.addVertexAttribute(vertexAttribute);
	}

	const VertexAttribute* VertexBufferFormat::getVertexAttributeFromSemantic(IndexedVertexAttributeSemantic semantic) const
	{
		for(auto&& attribute : mVertexAttributeVector)
		{
			if(attribute.getSemantic() == semantic)
			{
				return &attribute;
			}
		}
		return nullptr;
	}

	CLAIRE_NAMESPACE_END
}
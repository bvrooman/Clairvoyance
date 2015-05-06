#include "ClaireVertexFormat.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)
	
	VertexFormat::VertexFormat(void)
	{
	}

	VertexFormat::~VertexFormat(void)
	{
	}

	const VertexAttribute* VertexFormat::getVertexAttributeFromSemantic(IndexedVertexAttributeSemantic semantic) const
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

	bool VertexFormat::hasSemantic(IndexedVertexAttributeSemantic semantic) const
	{
		if(getVertexAttributeFromSemantic(semantic))
		{
			return true;
		}
		return false;
	}

	void VertexFormat::addVertexAttribute(const VertexAttribute& attribute)
	{
		if(!hasSemantic(attribute.getSemantic()))
		{
			mVertexAttributeVector.push_back(attribute);

			// Add the size of the attribute to the total size of the vertex
			mVertexSize += attribute.getSize();
		}
	}

	CLAIRE_NAMESPACE_END
}
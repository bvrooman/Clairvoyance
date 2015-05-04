#include "ClaireVertexFormat.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)
	
	VertexFormat::VertexFormat(void)
		: mVertexSize(0)
	{
	}

	VertexFormat::~VertexFormat(void)
	{
	}

	const VertexAttribute* VertexFormat::getVertexAttributeFromSemantic(IndexedVertexAttributeSemantic semantic) const
	{
		const VertexAttribute* ret = nullptr;
		for(
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
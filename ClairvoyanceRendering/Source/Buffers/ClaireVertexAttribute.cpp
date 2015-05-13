#include "ClaireVertexAttribute.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	VertexAttribute::VertexAttribute(
		IndexedVertexAttributeSemantic semantic,
		VertexAttributeType type,
		ushort count
		)
		: mSemantic(semantic)
		, mType(type)
		, mCount(count)
	{
	}

	ushort VertexAttribute::getTypeSize(void) const
	{
		switch(mType)
		{
		case VAT_FLOAT:
			return sizeof(float);
		case VAT_INT:
			return sizeof(int);
		case VAT_UINT:
			return sizeof(unsigned int);
		case VAT_SHORT:
			return sizeof(short);
		case VAT_USHORT:
			return sizeof(unsigned short);
		case VAT_BYTE:
			return sizeof(byte);
		case VAT_UBYTE:
			return sizeof(byte);
		default:
			return 0;
		}
	}

	ushort VertexAttribute::getSize(void) const
	{
		return getTypeSize() * mCount;
	}

	bool VertexAttribute::operator == (const VertexAttribute& other) const
	{
		if(mSemantic == other.getSemantic() &&
			mType == other.getType() &&
			mCount == other.getCount()
			)
		{
			return true;
		}
		return false;
	}

	bool VertexAttribute::operator != (const VertexAttribute& other) const
	{
		return !(*this == other);
	}

	CLAIRE_NAMESPACE_END
}
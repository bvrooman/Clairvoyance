#ifndef CLAIRE_VERTEX_ATTRIBUTE_H
#define CLAIRE_VERTEX_ATTRIBUTE_H

#include "ClaireRenderingPrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	enum VertexAttributeSemantic
	{
		// Position vector, 3 floats
		VAS_POSITION,

		// Normal vector, 3 floats 
		VAS_NORMAL,

		// 1 int (4 unsigned bytes)
		VAS_COLOUR,
		VAS_DIFFUSE_COLOUR,
		VAS_SPECULAR_COLOUR,

		// Tangent vector, 3 floats
		VAS_TANGENT,

		VAS_BITANGENT,

		// Texture coordinate vector, 2 floats
		VAS_TEXTURE_COORDINATE,

		VAS_BLEND_WEIGHT,

		VAS_BLEND_INDEX,
	};

	struct IndexedVertexAttributeSemantic
	{
		IndexedVertexAttributeSemantic(
			VertexAttributeSemantic semantic,
			size_t index = 0
			)
			: semantic(semantic)
			, index(index)
		{}

		VertexAttributeSemantic semantic;
		size_t index;

		bool operator == (const IndexedVertexAttributeSemantic& other) const
		{
			return 
				semantic == other.semantic &&
				index == other.index;
		}
		bool operator != (const IndexedVertexAttributeSemantic& other) const
		{
			return !(*this == other);
		}
	};

	enum VertexAttributeType
	{
		VAT_FLOAT,

		VAT_INT,

		VAT_UINT,

		VAT_SHORT,

		VAT_USHORT,

		VAT_BYTE,

		VAT_UBYTE
	};

	class CLAIRE_RENDERING_EXPORT VertexAttribute
	{
	public:
		VertexAttribute(
			IndexedVertexAttributeSemantic semantic,
			VertexAttributeType type,
			ushort count
			);
		~VertexAttribute(void);

		IndexedVertexAttributeSemantic getSemantic(void) const { return mSemantic; }
		VertexAttributeType getType(void) const { return mType; }
		ushort getCount(void) const { return mCount; }

		// Size of the vertex attribute type
		ushort getTypeSize(void) const;

		// Size of the vertex attribute type multiplied with the count
		ushort getSize(void) const;

		bool operator == (const VertexAttribute& other) const;
		bool operator != (const VertexAttribute& other) const;

	private:
		IndexedVertexAttributeSemantic mSemantic;
		VertexAttributeType mType;
		ushort mCount;
	};

	typedef ushort VertexAttributeHandle;

	CLAIRE_NAMESPACE_END
}

#endif
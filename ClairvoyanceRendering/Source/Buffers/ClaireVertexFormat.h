#ifndef CLAIRE_VERTEX_FORMAT_H
#define CLAIRE_VERTEX_FORMAT_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireSTLContainers.h"
#include "ClaireVertexAttribute.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	/*
	VertexFormat - defines the format of a single vertex that will
	be passed to the vertex shader. 
	A vertex is defined as an unsorted set of attributes, such as 
	position, normal, and colour. Pictorally, this is (VNC). The
	order of semantics is user defined, given by the order in which
	they are added.
	A vertex format is independent and agnostic of the buffer format. 
	Formats only dictate the order of vertex semantics.
	*/
	class CLAIRE_RENDERING_EXPORT VertexFormat
	{
	public:
		/*
		The set of unique attributes that defines this vertex.
		N.B. there is nothing that enforces the uniqueness of the
		set. Just don't add the same attribute twice, mkay?
		*/
		typedef vector<VertexAttribute> VertexAttributeVector;

	public:
		VertexFormat(void);
		~VertexFormat(void);

		/*
		Include a vertex attribute in this format definition.
		*/
		void addVertexAttribute(const VertexAttribute& attribute);

		const VertexAttribute* getVertexAttributeFromSemantic(IndexedVertexAttributeSemantic semantic) const;
		bool hasSemantic(IndexedVertexAttributeSemantic semantic) const;

		const VertexAttributeVector getVertexAttributeVector(void) const { return mVertexAttributeVector; }
		inline ushort getVertexSize(void) const { return mVertexSize; }

	private:
		VertexAttributeVector mVertexAttributeVector;
		ushort mVertexSize;
	};

	CLAIRE_NAMESPACE_END
}

#endif
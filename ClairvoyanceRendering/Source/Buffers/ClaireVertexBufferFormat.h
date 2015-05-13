#ifndef CLAIRE_VERTEX_BUFFER_FORMAT_H
#define CLAIRE_VERTEX_BUFFER_FORMAT_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireVertexAttribute.h"
#include "ClaireVertexFormat.h"
#include "ClaireSTLContainers.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_RENDERING_EXPORT VertexBufferFormat
	{
	public:
		typedef vector<VertexAttribute> VertexAttributeVector;

		enum SequenceType
		{
			// (VVVVNNNNCCCC)
			ST_SEQUENTIAL,

			// (VNCVNCVNCVNC)
			ST_INTERLEAVED
		};

	public:
		VertexBufferFormat(SequenceType sequence);
		~VertexBufferFormat(void) = default;

		void addVertexAttribute(VertexAttribute attribute);
		const VertexAttribute* getVertexAttributeFromSemantic(IndexedVertexAttributeSemantic semantic) const;

		SequenceType getSequenceType(void) const { return mSequenceType; }
		VertexAttributeVector getVertexAttributeVector(void) const { return mVertexAttributeVector; }
		VertexFormat getVertexFormatPiece(void) const { return mVertexFormatPiece; }
	private:
		SequenceType mSequenceType;

		/*
		The set of vertex attributes that compose the format of
		the related buffer object.
		*/
		VertexAttributeVector mVertexAttributeVector;

		/*
		The piece of the vertex format that makes up 
		this buffer format. In the case that this buffer format
		contains all attributes, this vertex format will be
		the same as the the vertex format used by the
		MeshManager.
		*/
		VertexFormat mVertexFormatPiece;
	};

	typedef std::unique_ptr<VertexBufferFormat> VertexBufferFormatUPtr;

	CLAIRE_NAMESPACE_END
}

#endif
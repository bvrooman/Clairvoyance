#ifndef CLAIRE_VERTEX_DATA_FORMAT_H
#define CLAIRE_VERTEX_DATA_FORMAT_H

#include "ClaireRenderingPrerequisites.h"

#include "Buffers\ClaireVertexFormat.h"
#include "Buffers\ClaireVertexBufferFormat.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class CLAIRE_RENDERING_EXPORT VertexDataFormat
	{
	public:
		static const size_t MAX_VERTEX_BUFFERS = 8;

	public:
		VertexDataFormat(void);
		~VertexDataFormat(void);

		VertexFormat getVertexFormat(void) const { return mVertexFormat; }
		VertexFormat& getVertexFormat(void) { return mVertexFormat; }

		VertexBufferFormat& createVertexBufferFormat(VertexBufferFormat::SequenceType sequenceType);
		
		VertexBufferFormat* getVertexBufferFormatForSemantic(IndexedVertexAttributeSemantic semantic) const;

		const VertexBufferFormat* const* getVertexBufferFormats(void) const;
		size_t getNumVertexBufferFormats(void) const;

	private:
		VertexFormat mVertexFormat;
		std::array<VertexBufferFormat*, MAX_VERTEX_BUFFERS> mVertexBufferFormats;
		size_t mNumVertexBufferFormats;
	};

	CLAIRE_NAMESPACE_END
}

#endif
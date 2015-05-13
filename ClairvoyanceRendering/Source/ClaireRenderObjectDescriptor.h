#ifndef CLAIRE_RENDER_OBJECT_DESCRIPTOR_H
#define CLAIRE_RENDER_OBJECT_DESCRIPTOR_H

#include "ClaireRenderingPrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class VertexData;
	class IndexData;

	class CLAIRE_RENDERING_EXPORT RenderObjectDescriptor
	{
	public:
		enum PrimitiveType
		{
			PT_POINT_LIST,

			PT_LINE_LIST,
			PT_LINE_STRIP,

			PT_TRIANGLE_LIST,
			PT_TRIANGLE_STRIP,
			PT_TRIANGLE_FAN
		};

	public:
		RenderObjectDescriptor(VertexData* vertexData, IndexData* indexData,
			PrimitiveType primitiveType
			)
			: mVertexData(vertexData)
			, mIndexData(indexData)
			, mPrimitiveType(primitiveType)
		{}
		~RenderObjectDescriptor(void) = default;

		VertexData* getVertexData(void) const { return mVertexData; }
		IndexData* getIndexData(void) const { return mIndexData; }
		PrimitiveType getPrimitiveType(void) const { return mPrimitiveType; }

	private:
		VertexData* mVertexData = nullptr;
		IndexData* mIndexData = nullptr;
		PrimitiveType mPrimitiveType = PT_POINT_LIST;
	};

	CLAIRE_NAMESPACE_END
}

#endif
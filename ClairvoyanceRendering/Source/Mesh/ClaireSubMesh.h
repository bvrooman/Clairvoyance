#ifndef CLAIRE_SUB_MESH_H
#define CLAIRE_SUB_MESH_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireVertexData.h"
#include "ClaireIndexData.h"
#include "ClaireRenderObjectDescriptor.h"
#include "ClaireAxisAlignedBoundingBox.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class Mesh;

	class CLAIRE_RENDERING_EXPORT SubMesh
	{
		CLAIRE_MOVABLE_ONLY(SubMesh)

	public:
		static const ushort MAX_TEXTURE_COORDINATES = 8;
		static const ushort MAX_COLOUR_SETS = 8;

	public:
		SubMesh(Mesh* parentMesh);
		~SubMesh(void);

		Mesh* getParentMesh(void) const { return mParentMesh; }

		VertexData* getVertexData(void) const { return mVertexData.get(); }
		IndexData* getIndexData(void) const { return mIndexData.get(); }

		RenderObjectDescriptor getRenderObjectDescriptor(void) const;

		void calculateAABBFromBuffer(void);

		AxisAlignedBoundingBox getAABB(void) const { return mAABB; }

	private:
		Mesh* mParentMesh;

		RenderObjectDescriptor::PrimitiveType mPrimitiveType;

		VertexDataUPtr mVertexData;
		IndexDataUPtr mIndexData;

		AxisAlignedBoundingBox mAABB;
	};

	typedef std::unique_ptr<SubMesh> SubMeshUPtr;

	CLAIRE_NAMESPACE_END
}

#endif
#include "ClaireSubMesh.h"
#include "ClaireMesh.h"
#include "ClaireMeshManager.h"
#include "Buffers\ClaireVertexBufferObject.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	SubMesh::SubMesh(Mesh* parentMesh)
		: mParentMesh(parentMesh)
		, mPrimitiveType(RenderObjectDescriptor::PT_TRIANGLE_LIST)
	{
		mVertexData = std::make_unique<VertexData>();
		mIndexData = std::make_unique<IndexData>();
	}

	SubMesh::~SubMesh(void)
	{

	}

	RenderObjectDescriptor SubMesh::getRenderObjectDescriptor(void) const
	{
		RenderObjectDescriptor operation(
			mVertexData.get(),
			mIndexData.get(),
			mPrimitiveType
			);
		return operation;
	}

	void SubMesh::calculateAABBFromBuffer(void)
	{
		MeshManager* meshManager = (MeshManager*)mParentMesh->getManager();

		VertexData::VertexBufferObjectHandle vboHandle =
			mVertexData->getVBOHandleFromSemantic(VAS_POSITION);
		VertexBufferObject* vbo = nullptr;
		
		if(vboHandle != VertexData::INVALID_HANDLE)
		{
			vbo = mVertexData->getVertexBufferObject(vboHandle);
		}

		if(!vbo)
		{
			return;
		}

		// Calculate the AABB from vertex data
		union
		{
			void* pVertexData;
			byte* bytes;
		};
		
		pVertexData = vbo->lock(BufferObject::LS_READ);
		
		AxisAlignedBoundingBox aabb;
		size_t numVertices = vbo->getNumVertices();
		size_t vertexSize = vbo->getVertexSize();
		for (size_t i = 0; i < numVertices; i++)
		{
			float* positions = static_cast<float*>(pVertexData);
			Vector3 position(positions[0], positions[1], positions[2]);
			aabb.merge(AxisAlignedBoundingBox(position, position));

			bytes += vertexSize;
		}

		vbo->unlock();

		mAABB.clear();
		mAABB.merge(aabb);
	}

	CLAIRE_NAMESPACE_END
}
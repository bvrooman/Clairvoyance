#ifndef CLAIRE_MESH_H
#define CLAIRE_MESH_H

#include "ClaireRenderingPrerequisites.h"

#include "Resource\ClaireResource.h"

#include "ClaireSTLContainers.h"

#include "Buffers\ClaireBufferObject.h"
#include "ClaireSubMesh.h"

#include "ClaireAxisAlignedBoundingBox.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	using namespace core;

	class MeshManager;

	class CLAIRE_RENDERING_EXPORT Mesh
		: public Resource
	{
		CLAIRE_MOVABLE_ONLY(Mesh)

	private:
		typedef	vector<SubMeshUPtr> SubMeshList;
		typedef vector<SubMesh*> SubMeshPtrList;

	public:
		Mesh(const string& name, const string& path, ResourceManager* manager);
		~Mesh(void) = default;

		SubMesh* createSubMesh(void);

		void calculateAABB(void);
		AxisAlignedBoundingBox getAABB(void) const { return mAABB; }

		EnumFlags getVertexBufferUsageSettingsFlags(void) const { return mVertexBufferUsageSettingsFlags; }
		EnumFlags getIndexBufferUsageSettingsFlags(void) const { return mIndexBufferUsageSettingsFlags; }

		SubMeshPtrList getSubMeshList(void) const { return mSubMeshPtrList; }

	protected:
		void preload_(void) CLAIRE_OVERRIDE;
		void load_(void) CLAIRE_OVERRIDE;
		void postload_(void) CLAIRE_OVERRIDE;
		void unload_(void) CLAIRE_OVERRIDE;

		void calculateSize(void) CLAIRE_OVERRIDE;

	private:
		MeshManager* mMeshManager = nullptr;

		EnumFlags mVertexBufferUsageSettingsFlags = BufferObject::US_WRITE_ONLY;
		EnumFlags mIndexBufferUsageSettingsFlags = BufferObject::US_WRITE_ONLY;

		SubMeshList mSubMeshList;
		SubMeshPtrList mSubMeshPtrList;

		AxisAlignedBoundingBox mAABB;
	};

	CLAIRE_NAMESPACE_END
}

#endif
#include "ClaireMesh.h"

#include "ClaireMeshSerializer.h"
#include "Mesh\ClaireIMeshSerializerAdapter.h"

#include "ClaireMeshManager.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	Mesh::Mesh(const string& name, const string& path, ResourceManager* manager)
		: Resource(name, path, manager)
	{
		mMeshManager = static_cast<MeshManager*>(mManager);
	}

	SubMesh* Mesh::createSubMesh(void)
	{
		auto subMesh = std::make_unique<SubMesh>(this);
		SubMesh* subMesh_ = subMesh.get();
		mSubMeshList.push_back(std::move(subMesh));
		mSubMeshPtrList.push_back(subMesh_);
		return subMesh_;
	}

	void Mesh::calculateAABB(void)
	{
		mAABB.clear();
		for(auto && subMesh : mSubMeshList)
		{
			mAABB.merge(subMesh->getAABB());
		}
	}

	void Mesh::preload_(void)
	{
	}

	void Mesh::load_(void)
	{
		IMeshSerializerAdapter* adapter = mMeshManager->getMeshSerializerAdapter();
		MeshSerializer meshSerializer(adapter);

		meshSerializer.importMesh(mPath, this);
	}

	void Mesh::postload_(void)
	{
		for(auto&& subMesh : mSubMeshList)
		{
			subMesh->calculateAABBFromBuffer();
		}
		calculateAABB();
	}

	void Mesh::unload_(void)
	{
	}

	void Mesh::calculateSize(void)
	{
	}

	CLAIRE_NAMESPACE_END
}
#ifndef CLAIRE_MESH_MANAGER_H
#define CLAIRE_MESH_MANAGER_H

#include "ClaireRenderingPrerequisites.h"

#include "Resource\ClaireResourceManager.h"
#include "Mesh\ClaireIMeshSerializerAdapter.h"

#include "Mesh\ClaireVertexDataFormat.h"

namespace Claire
{
	using namespace core;

	CLAIRE_NAMESPACE_BEGIN(rendering)

	class BufferObjectManager;
	class Mesh;

	class CLAIRE_RENDERING_EXPORT MeshManager
		: public ResourceManager
	{
	public:
		MeshManager(BufferObjectManager* bufferObjectManager);
		~MeshManager(void) = default;

		Mesh* getMesh(const string& name) const;

		BufferObjectManager* getBufferObjectManager(void) const { return mBufferObjectManager; }
		IMeshSerializerAdapter* getMeshSerializerAdapter(void) const { return mSerializerAdapter.get(); }

		VertexDataFormat* getPreferredVertexDataFormat(void) { return &mPreferredVertexDataFormat; }

	private:
		Resource* createResource_(
			const string& name,
			const string& path
			) CLAIRE_OVERRIDE;

	private:
		BufferObjectManager* mBufferObjectManager;

		VertexDataFormat mPreferredVertexDataFormat;

		MeshSerializerAdapterUPtr mSerializerAdapter;
	};

	CLAIRE_NAMESPACE_END
}

#endif
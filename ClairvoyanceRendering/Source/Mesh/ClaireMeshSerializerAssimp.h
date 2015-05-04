#ifndef CLAIRE_MESH_SERIALIZER_ASSIMP_H
#define CLAIRE_MESH_SERIALIZER_ASSIMP_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireIMeshSerializerAdapter.h"

#include <assimp\scene.h>
#include <assimp\postprocess.h>

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class MeshManager;
	class SubMesh;
	class BufferObjectManager;
	class VertexBufferFormat;
	class VertexBufferObject;

	class CLAIRE_RENDERING_EXPORT MeshSerializerAssimp
		: public IMeshSerializerAdapter
	{
	public:
		MeshSerializerAssimp(MeshManager* meshManager);
		~MeshSerializerAssimp(void);

		void importMesh(const string& path, Mesh* dest) CLAIRE_OVERRIDE;

	private:
		void processScene(const aiScene* scene, Mesh* dest);
		void readSubMesh(const aiScene* scene, const aiMesh* rawSubMesh, SubMesh* subMesh);
		void readIndices(const aiMesh* rawSubMesh, SubMesh* subMesh);
		void readVertexGeometry(const aiMesh* rawSubMesh, SubMesh* subMesh);

		void readVertexGeometryBuffer(const aiMesh* rawSubMesh, VertexBufferFormat* format, VertexBufferObject* vbo);
		void readVertexGeometryBufferSequential(const aiMesh* rawSubMesh, VertexBufferFormat* format, VertexBufferObject* vbo);
		void readVertexGeometryBufferInterleaved(const aiMesh* rawSubMesh, VertexBufferFormat* format, VertexBufferObject* vbo);

	private:
		MeshManager* mMeshManager;
		BufferObjectManager* mBufferObjectManager;
	};

	CLAIRE_NAMESPACE_END
}

#endif
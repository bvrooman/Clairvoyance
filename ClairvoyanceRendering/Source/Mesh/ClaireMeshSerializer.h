#ifndef CLAIRE_MESH_SERIALIZER_H
#define CLAIRE_MESH_SERIALIZER_H

#include "ClaireRenderingPrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class Mesh;
	class IMeshSerializerAdapter;

	class CLAIRE_RENDERING_EXPORT MeshSerializer
	{
	public:
		MeshSerializer(IMeshSerializerAdapter* serializer);
		~MeshSerializer(void) = default;

		void importMesh(const string& path, Mesh* dest);

	private:
		IMeshSerializerAdapter* mSerializer;
	};

	CLAIRE_NAMESPACE_END
}

#endif
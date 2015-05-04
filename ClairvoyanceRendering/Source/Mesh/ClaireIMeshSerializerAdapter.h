#ifndef CLAIRE_I_MESH_SERIALIZER_ADAPTER_H
#define CLAIRE_I_MESH_SERIALIZER_ADAPTER_H

#include "ClaireRenderingPrerequisites.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class Mesh;

	class CLAIRE_RENDERING_EXPORT IMeshSerializerAdapter
	{
	public:
		virtual void importMesh(const string& path, Mesh* dest) CLAIRE_ABSTRACT;
	};

	typedef std::unique_ptr<IMeshSerializerAdapter> MeshSerializerAdapterUPtr;

	CLAIRE_NAMESPACE_END
}

#endif
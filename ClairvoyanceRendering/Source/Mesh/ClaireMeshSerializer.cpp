#include "ClaireMeshSerializer.h"
#include "ClaireIMeshSerializerAdapter.h"

#include <sys\stat.h>

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	MeshSerializer::MeshSerializer(IMeshSerializerAdapter* serializer)
		: mSerializer(serializer)
	{

	}

	MeshSerializer::~MeshSerializer(void)
	{

	}

	void MeshSerializer::importMesh(const string& path, Mesh* dest)
	{
		struct stat buffer;
		int exists = stat(path.c_str(), &buffer);

		if(exists == 0)
		{
			mSerializer->importMesh(path, dest);
		}
		else
		{
			assert(false && "Unable to find file.\n");
		}
	}

	CLAIRE_NAMESPACE_END
}
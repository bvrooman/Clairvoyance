#include "ClaireEntityFactory.h"

#include "Mesh\ClaireMesh.h"
#include "Mesh\ClaireMeshManager.h"

#include "ClaireEntity.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	const string EntityFactory::MESH_NAME_KEY = "MESH_NAME";

	EntityFactory::EntityFactory(MeshManager* meshManager)
		: mMeshManager(meshManager)
	{
	}

	SceneObject* EntityFactory::createSceneObject_(const string& name, const ParamMap* paramMap)
	{
		ParamMap::const_iterator it = paramMap->find(MESH_NAME_KEY);

		if(it != paramMap->end())
		{
			string meshName = it->second;
			Mesh* mesh = (Mesh*)mMeshManager->getResource(meshName);

			if(mesh)
			{
				return mManagerImpl.create<Entity>(
					name,
					name, mesh
					);
			}
			else
			{
				assert(false && "Mesh not found");
			}
		}
		return nullptr;
	}

	CLAIRE_NAMESPACE_END
}
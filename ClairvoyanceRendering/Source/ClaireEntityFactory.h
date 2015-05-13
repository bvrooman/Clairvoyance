#ifndef CLAIRE_ENTITY_FACTORY_H
#define CLAIRE_ENTITY_FACTORY_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireSceneObjectFactory.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class MeshManager;

	class CLAIRE_RENDERING_EXPORT EntityFactory
		: public SceneObjectFactory
	{
	public:
		static const string MESH_NAME_KEY;

	public:
		EntityFactory(MeshManager* meshManager);
		~EntityFactory(void) = default;

	private:
		SceneObject* createSceneObject_(const string& name, const ParamMap* paramMap) CLAIRE_OVERRIDE;

	private:
		MeshManager* mMeshManager = nullptr;
	};

	CLAIRE_NAMESPACE_END
}

#endif
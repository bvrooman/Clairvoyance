#include "ClaireEntity.h"

#include "Mesh\ClaireMesh.h"
#include "Mesh\ClaireMeshManager.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	Entity::Entity(const string& name, Mesh* mesh)
		: SceneObject(name)
		, mMesh(mesh)
		, mInitialized(false)
	{

	}

	Entity::~Entity(void)
	{

	}

	void Entity::initialize(void)
	{
		if(mInitialized)
		{
			return;
		}

		if(mMesh)
		{
			mMesh->load();
		}

		mInitialized = true;
	}

	void Entity::calculateLocalAABB(void)
	{
		mLocalAABB = mMesh->getAABB();
	}

	CLAIRE_NAMESPACE_END
}
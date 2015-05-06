#include "ClaireSceneObject.h"

#include "ClaireSceneNode.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	SceneObject::SceneObject(const string& name)
		: mName(name)
	{
	}

	SceneObject::~SceneObject(void)
	{
	}

	void SceneObject::attachToSceneNode(SceneNode* sceneNode)
	{
		mParentSceneNode = sceneNode;
	}

	void SceneObject::calculateWorldAABB(void)
	{
		calculateLocalAABB();
		mWorldAABB = mLocalAABB;

		if(mParentSceneNode)
		{
			// To get the world AABB, we must transform the
			// local AABB by the scene node's world transform.
			// Before we apply the world transform, we must make
			// sure that it has been derived.
			mParentSceneNode->forceUpdateDerivedTransform();

			Transform t = mParentSceneNode->getDerivedTransform();
			mWorldAABB.applyTransform(t);
		}
	}

	CLAIRE_NAMESPACE_END
}
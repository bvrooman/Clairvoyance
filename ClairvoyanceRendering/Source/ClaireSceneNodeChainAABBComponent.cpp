#include "ClaireSceneNodeChainAABBComponent.h"
#include "ClaireSceneNode.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	SceneNodeChainAABBComponent::SceneNodeChainAABBComponent(void)
	{
		mTaggedForClear.fill(true);
	}

	void SceneNodeChainAABBComponent::addNode(Node* node)
	{
		NodeHandle handle = node->getNodeHandle();

		SceneNode* sceneNode = static_cast<SceneNode*>(node);
		sceneNode->setSceneObjectAABBReference(&mSceneObjectAABBs[handle]);
		sceneNode->setWorldAABBReference(&mWorldAABBs[handle]);
	}

	void SceneNodeChainAABBComponent::update(NodeHandle handle, FlatNode node)
	{
		updateAABBs(handle, node);

		// If we reach the root node, we have finished updating. Tag
		// all AABBs to be cleared (reset).
		if(handle == 0)
		{
			mTaggedForClear.fill(true);
		}
	}

	void SceneNodeChainAABBComponent::updateAABBs(NodeHandle handle, FlatNode node)
	{
		// If the AABB needs to be cleared, do so
		if(mTaggedForClear[handle])
		{
			mWorldAABBs[handle].clear();
			mTaggedForClear[handle] = false;
		}

		// Merge the scene object AABB with the world AABB
		mWorldAABBs[handle].merge(mSceneObjectAABBs[handle]);

		// If the handle is 0, then it is the root node and has no parent
		// Update the parent only if it is not the root node
		if(handle != 0)
		{
			const NodeHandle parentHandle = node.parentHandle;

			// If the parent AABB needs to be cleared, do so
			if(mTaggedForClear[parentHandle])
			{
				mWorldAABBs[parentHandle].clear();
				mTaggedForClear[parentHandle] = false;
			}

			// Merge upwards so that the parent AABB includes this AABB
			mWorldAABBs[parentHandle].merge(mWorldAABBs[handle]);
		}
	}

	CLAIRE_NAMESPACE_END
}
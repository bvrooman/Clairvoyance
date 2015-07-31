#include "ClaireNodeChainTransformComponent.h"

#include "ClaireNode.h"
#include "ClaireNodeChain.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	void NodeChainTransformComponent::addNode(Node* node)
	{
		NodeHandle handle = node->getHandle();

		// Save the transform the node is added with
		const Transform transform = node->getTransform();
		mLocalTransforms[handle] = transform;

		// Link the local and derived transforms to this node
		node->setTransformSource(&mLocalTransforms[handle]);
		node->setDerivedTransformSource(&mDerivedTransforms[handle]);
	}

	void NodeChainTransformComponent::update(NodeHandle handle, FlatNode node)
	{
		if(mDirty)
		{
			if(node.parentHandle < mDirtyNode)
			{
				mDirty = false;
			}
		}

		// Determine if any of the derived transforms in the set
		// are out of date
		if(mCachedLocalTransforms[handle] != mLocalTransforms[handle])
		{
			// Store the node that starts the dirty branch
			mDirtyNode = handle;
			mDirty = true;
			mCachedLocalTransforms[handle] = mLocalTransforms[handle];
		}

		if(mDirty)
		{
			calculateDerivedTransform(handle, node);
		}
	}

	void NodeChainTransformComponent::calculateDerivedTransform(NodeHandle handle, FlatNode node)
	{
		// Update the derived transforms
		// If the handle is 0, then it is the root node
		if(handle == 0)
		{
			mDerivedTransforms[handle] = mLocalTransforms[handle];
		}
		else
		{
			const NodeHandle parentHandle = node.parentHandle;
			const Matrix4 parentT = mDerivedTransforms[parentHandle].asHomogeneousMatrix();
			const Matrix4 localT = mLocalTransforms[handle].asHomogeneousMatrix();
			mDerivedTransforms[handle] = parentT * localT;
		}
	}

	CLAIRE_NAMESPACE_END
}
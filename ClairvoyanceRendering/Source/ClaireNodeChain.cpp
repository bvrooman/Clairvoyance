#include "ClaireNodeChain.h"

#include "ClaireNode.h"
#include "ClaireINodeChainComponent.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	NodeChain::NodeChain(Node* rootNode)
		: mRootNode(rootNode)
		, mBuildNeeded(true)
		, mCurrentHandle(0)
	{
		mComponentVector.reserve(4);
		mUpdatePassList.reserve(2);
		mManualUpdatePassList.reserve(2);
	}

	NodeChain::~NodeChain(void)
	{
	}

	void NodeChain::addNode(Node* node)
	{
		// Assign the node a handle
		node->mHandle = mCurrentHandle;

		// Add the node to each component
		for_each(mComponentVector.begin(), mComponentVector.end(), [&](NodeChainComponentUPtr& component)
		{
			component->addNode(node);
		});

		// Increment the handle so that it can be used for the next node
		mCurrentHandle++;
	}

	void NodeChain::setNodeParent(NodeHandle handle, NodeHandle parent)
	{
		mNodes[handle].parentHandle = parent;
	}

	void NodeChain::notifyChildAdded(NodeHandle handle)
	{
		mNodes[handle].numChildren++;
	}

	void NodeChain::notifyBuildNeeded(void)
	{
		mBuildNeeded = true;
	}

	void NodeChain::build(void)
	{
		// See if the node chain needs to be built or rebuilt
		if(mBuildNeeded)
		{
			// Reset the handle used to build the node chain
			mCurrentHandle = 0;

			// We must build the node chain such that it follows a
			// PRE-ORDER depth traversal
			mRootNode->buildNodeChain();

			// Build complete
			mBuildNeeded = false;

			/*
			size_t sz = mRootNode->getTreeSize();
			for (size_t i = 0; i < sz; i++)
			{
				std::cout << mNodes[i].handle << " : " << mNodes[i].parentHandle << " : " << mNodes[i].numChildren << "\n";
			}
			*/
		}
	}

	const FlatNode* NodeChain::getFlatNodeData(void) const
	{
		return mNodes.data();
	}

	void NodeChain::update(const Node* node)
	{
		build();

		// Update the nodes in the set [start, end), where
		//	start = node
		//	end = last child node of node's branch
		NodeHandle start = node->mHandle;
		NodeHandle end = start + 1;

		for(NodeHandle i = start; i < end; i++)
		{
			// Increase the size of the update set to include children
			end += getFlatNodeData()[i].numChildren;
		}

		// Update each pass
		for_each(mUpdatePassList.begin(), mUpdatePassList.end(), [&](UpdatePassUPtr& pass)
		{
			pass->update(
				start,
				end,
				getFlatNodeData()
				);
		});
	}

	
	NodeChain::UpdatePass::UpdatePass(NodeChain::UpdatePassOrder order)
		: mOrder(order)
	{
		mComponentVector.reserve(4);
	}

	void NodeChain::UpdatePass::addComponent(INodeChainComponent* component)
	{
		mComponentVector.push_back(component);
	}

	void NodeChain::UpdatePass::update(NodeHandle start, NodeHandle end, const FlatNode nodes[])
	{
		switch(mOrder)
		{
		case UPO_PRE_ORDER:
			for_each(mComponentVector.begin(), mComponentVector.end(), [&](INodeChainComponent* component)
			{
				for(NodeHandle i = start; i < end; i++)
				{
					component->update(
						i,
						nodes[i]
						);
				}
			});
			break;

		case UPO_POST_ORDER:
			for_each(mComponentVector.begin(), mComponentVector.end(), [&](INodeChainComponent* component)
			{
				for(NodeHandle i = end; i-- > start;)
				{
					component->update(
						i,
						nodes[i]
						);
				}
			});
			break;
		}
	}

	CLAIRE_NAMESPACE_END
}
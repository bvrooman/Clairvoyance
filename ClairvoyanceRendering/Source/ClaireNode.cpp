#include "ClaireNode.h"

#include "ClaireNodeChainTransformComponent.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	NameGenerator Node::sNameGenerator("UnnamedNode");

	Node::Node(
		const string& name,
		const Transform& transform
		)
		: mName(name)
		, mHandle(0)
		, mParentNode(nullptr)
		, mTransform(nullptr)
		, mDerivedTransform(nullptr)
		, mInitialTransform(transform)
	{
		createNodeChain();
		setup();
	}

	Node::Node(
		const Transform& transform
		)
		: mParentNode(nullptr)
		, mTransform(nullptr)
		, mDerivedTransform(nullptr)
		, mInitialTransform(transform)
	{
		mName = sNameGenerator.generate();
		createNodeChain();
		setup();
	}

	void Node::setup(void)
	{
		INodeChainComponent* transformComp = mNodeChain->createComponent<NodeChainTransformComponent>();

		mTransformPass = mNodeChain->createManualUpdatePass(NodeChain::UPO_PRE_ORDER);
		mTransformPass->addComponent(transformComp);

		NodeChain::UpdatePass* preorderPass = mNodeChain->createUpdatePass(NodeChain::UPO_PRE_ORDER);
		preorderPass->addComponent(transformComp);
	}

	Node::Node(
		NodeChainSPtr nodeChain,
		const string& name,
		const Transform& transform
		)
		: mNodeChain(nodeChain)
		, mName(name)
		, mParentNode(nullptr)
		, mTransform(nullptr)
		, mDerivedTransform(nullptr)
		, mInitialTransform(transform)
	{
		mTransformPass = mNodeChain->getManualUpdatePass(0);
	}

	Node::Node(
		NodeChainSPtr nodeChain,
		const Transform& transform
		)
		: mNodeChain(nodeChain)
		, mParentNode(nullptr)
		, mTransform(nullptr)
		, mDerivedTransform(nullptr)
		, mInitialTransform(transform)
	{
		mName = sNameGenerator.generate();
		mTransformPass = mNodeChain->getManualUpdatePass(0);
	}

	Node::~Node(void)
	{
	}

	Transform Node::getTransform(void) const
	{
		if(mTransform)
		{
			return *mTransform;
		}
		return mInitialTransform;
	}

	Transform& Node::getTransform(void)
	{
		if(mTransform)
		{
			return *mTransform;
		}
		return mInitialTransform;
	}

	Transform Node::getDerivedTransform(void) const
	{
		return *mDerivedTransform;
	}

	void Node::forceUpdateDerivedTransform(void) const
	{
		NodeHandle start = mNodeChain->getRootNode()->getNodeHandle();
		NodeHandle end = start + 1;

		for(NodeHandle i = start; i < end; i++)
		{
			// Increase the size of the update set to include children
			end += mNodeChain->getFlatNodeData()[i].numChildren;
		}

		mTransformPass->update(
			start,
			end,
			mNodeChain->getFlatNodeData()
			);
	}

	void Node::createNodeChain(void)
	{
		// Reset the handle
		mHandle = 0;

		// Remove pointers to the old node chain, if any
		mTransform = nullptr;
		mDerivedTransform = nullptr;

		setNodeChain(
			std::make_shared<NodeChain>(this)
			);
	}

	void Node::buildNodeChain(void)
	{
		buildNodeChain_();
	}

	void Node::buildNodeChain_(void)
	{
		// PRE-ORDER traversal for adding nodes to the node chain

		// Add this node to the node chain
		addToChain();

		// For each child node:
		for_each(mChildNodeVector.begin(), mChildNodeVector.end(), [&](Node* child)
		{
			// Recursively add the child node to the node chain
			child->buildNodeChain_();

			// Notify the child node in the node chain to
			// set its parent to this node
			mNodeChain->setNodeParent(child->mHandle, mHandle);
			
			// Notify this node in the node chain to
			// tell it a child has been added
			mNodeChain->notifyChildAdded(mHandle);
		});
	}

	void Node::setNodeChain(NodeChainSPtr nodeChain)
	{
		mNodeChain = nodeChain;
		for_each(mChildNodeVector.begin(), mChildNodeVector.end(), [&](Node* child)
		{
			child->setNodeChain(nodeChain);
		});
	}

	void Node::addToChain(void)
	{
		mNodeChain->addNode(this);
	}

	void Node::update(void)
	{
		mNodeChain->build();

		// Update subclass
		update_();

		mNodeChain->update(this);
	}

	Node* Node::createChild(
		const string& name,
		const Transform& transform
		)
	{
		auto node = create_(
			name, transform
			);
		Node* node_ = node.get();
		attachChild(std::move(node));
		return node_;
	}

	Node* Node::createChild(
		const Transform& transform
		)
	{
		return createChild(
			sNameGenerator.generate(),
			transform
			);
	}

	size_t Node::getTreeSize(void) const
	{
		return getTreeSize_(0);
	}
	
	size_t Node::getTreeSize_(size_t count) const
	{
		count++;

		for_each(mChildNodeVector.begin(), mChildNodeVector.end(), [&](Node* child)
		{
			count = child->getTreeSize_(count);
		});

		return count;
	}

	Node* Node::attachChild(NodeUPtr child)
	{
		string name = child->getName();
		
		if(child->mParentNode)
		{
			// Detach the node from its current parent
			child->mParentNode->detachChild(name);
		}

		mNodeChain->notifyBuildNeeded();

		// Set the child's new parent to this
		child->setParent(this);

		// If the child comes from a different node chain,
		// merge it with this one
		if(child->mNodeChain != mNodeChain)
		{
			child->setNodeChain(mNodeChain);
		}

		Node* child_ = child.get();

		mChildNodeVector.push_back(child.get());
		mNodeManager.attach(name, child);

		return child_;
	}

	NodeUPtr Node::detachChild(const string& name)
	{
		NodeUPtr child = mNodeManager.detach(name);
		if(!child)
		{
			return nullptr;
		}

		mNodeChain->notifyBuildNeeded();

		// Find the child node's current position and 
		// store it so we can later retrieve it for its own chain.
		// Why do we check for a derived transform? In the case
		// that an update call has not been made yet, the derived
		// transform will not have been calculated. We must use
		// the initial transform that was provided at creation
		// time.
		child->mInitialTransform = child->mDerivedTransform ? 
			*child->mDerivedTransform :
			child->mInitialTransform;
		
		// Set the node's new parent to null
		child->setParent(nullptr);

		// Now the child is parentless, treat it as a root and
		// create a new node chain for it and all its children
		child->createNodeChain();	
		
		Node* n = child.get();
		mChildNodeVector.erase(
			std::remove(mChildNodeVector.begin(), mChildNodeVector.end(), n),
			mChildNodeVector.end()
			);

		return child;
	}

	void Node::setParent(Node* parent)
	{
		mParentNode = parent;
	}

	CLAIRE_NAMESPACE_END
}
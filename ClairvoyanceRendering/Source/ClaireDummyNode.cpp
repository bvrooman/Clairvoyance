#include "ClaireDummyNode.h"

#include "ClaireNodeChainTransformComponent.h"
#include "ClaireNodeChainDummyComponent.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	DummyNode::DummyNode(
		const string& name,
		const Transform& transform
		)
		: Node(name, transform)
	{
		setup();
	}

	DummyNode::DummyNode(
		const Transform& transform
		)
		: Node(transform)
	{
		setup();
	}

	void DummyNode::setup(void)
	{
		//INodeChainComponent* transformComp = mNodeChain->createComponent<NodeChainTransformComponent>();
		//INodeChainComponent* dummyComp = mNodeChain->createComponent<NodeChainDummyComponent>();

		//NodeChain::UpdatePass* p = mNodeChain->createUpdatePass(NodeChain::UPO_PRE_ORDER);
		//p->addComponent(transformComp);
		//p->addComponent(dummyComp);

		//NodeChain::UpdatePass* p2 = mNodeChain->createUpdatePass(NodeChain::UPO_POST_ORDER);
		//p2->addComponent(dummyComp);
	}

	DummyNode::DummyNode(
		NodeChainSPtr nodeChain,
		const string& name,
		const Transform& transform
		)
		: Node(nodeChain, name, transform)
	{}
	DummyNode::DummyNode(
		NodeChainSPtr nodeChain,
		const Transform& transform
		)
		: Node(nodeChain, transform)
	{}

	NodeUPtr DummyNode::create_(
		const string& name,
		const Transform& transform
		)
	{
		NodeUPtr node = NodeUPtr(new DummyNode(
			mNodeChain, name, transform
			));
		return node;
	}

	CLAIRE_NAMESPACE_END
}
#include "ClaireDummyNode.h"

#include "ClaireNodeChainTransformComponent.h"
#include "ClaireNodeChainDummyComponent.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	NameGenerator DummyNode::sNameGenerator("UnnamedDummyNode");

	DummyNode::DummyNode(
		const string& name
		)
		: DummyNode(
			name,
			Transform()
			)
	{
	}

	DummyNode::DummyNode(
		const Transform& transform
		)
		: DummyNode(
			sNameGenerator.generate(),
			transform
			)
	{
	}

	DummyNode::DummyNode(
		const string& name,
		const Transform& transform
		)
		: Node(name, transform)
	{
		INodeChainComponent* dummyComponent = mNodeChain->createComponent<NodeChainDummyComponent>();
		mNodeChain->getUpdatePass(0)->addComponent(dummyComponent);

		NodeChain::UpdatePass* p = mNodeChain->createUpdatePass(NodeChain::UPO_POST_ORDER);
		p->addComponent(dummyComponent);
	}

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
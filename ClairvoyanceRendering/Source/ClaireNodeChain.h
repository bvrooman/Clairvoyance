#ifndef CLAIRE_NODE_CHAIN_H
#define CLAIRE_NODE_CHAIN_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireFlatNode.h"
#include "ClaireINodeChainComponent.h"
#include "ClaireSTLContainers.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)
		 
	class Node;

	class CLAIRE_RENDERING_EXPORT NodeChain
	{
		CLAIRE_MOVABLE_ONLY(NodeChain)

	public:
		enum UpdatePassOrder
		{
			// Pre-order traversal
			UPO_PRE_ORDER,

			// Pseudo post-order traversal
			// Instead of true post-order, this setting
			// traverses the tree in reverse pre-order
			UPO_POST_ORDER,
		};

		class UpdatePass;
		typedef std::unique_ptr<UpdatePass> UpdatePassUPtr;

	private:
		static const size_t CHAIN_SIZE = MAX_NODE_CHAIN_SIZE;

	public:
		NodeChain(Node* rootNode);
		virtual ~NodeChain(void);

		inline void addNode(Node* node);
		inline void setNodeParent(NodeHandle handle, NodeHandle parent);
		inline void notifyChildAdded(NodeHandle handle);

		inline void notifyBuildNeeded(void);
		inline void build(void);

		inline Node* getRootNode(void) const { return mRootNode; }

		inline const FlatNode* getFlatNodeData(void) const;

		UpdatePass* createUpdatePass(UpdatePassOrder order)
		{
			auto p = std::make_unique<UpdatePass>(order);
			UpdatePass* p_ = p.get();
			mUpdatePassList.push_back(
				std::move(p)
				);
			return p_;
		}

		UpdatePass* createManualUpdatePass(UpdatePassOrder order)
		{
			auto p = std::make_unique<UpdatePass>(order);
			UpdatePass* p_ = p.get();
			mManualUpdatePassList.push_back(
				std::move(p)
				);
			return p_;
		}

		UpdatePass* getManualUpdatePass(size_t index)
		{
			return mManualUpdatePassList[index].get();
		}

		template<typename T>
		T* createComponent(void)
		{
			auto p = std::make_unique<T>();
			T* p_ = p.get();
			mComponentVector.push_back(
				std::move(p)
				);
			return p_;
		}

		inline void update(const Node* node);

	private:
		Node* mRootNode = nullptr;

		bool mBuildNeeded = true;

		typedef vector<UpdatePassUPtr> UpdatePassList;
		UpdatePassList mUpdatePassList;
		UpdatePassList mManualUpdatePassList;

		typedef vector<NodeChainComponentUPtr> ComponentVector;
		ComponentVector mComponentVector;

		// A monotonically increasing handle assigned to each node
		// when adding it to the chain
		NodeHandle mCurrentHandle = 0;

		// Flat nodes
		std::array<FlatNode, CHAIN_SIZE> mNodes;
	};

	typedef std::shared_ptr<NodeChain> NodeChainSPtr;


	class NodeChain::UpdatePass
	{
	public:
		UpdatePass(UpdatePassOrder order);

		void addComponent(INodeChainComponent* component);
		void update(NodeHandle start, NodeHandle end, const FlatNode nodes[]);

	private:
		UpdatePassOrder mOrder;
		const FlatNode* mFlatNodes;

		typedef vector<INodeChainComponent*> ComponentList;
		ComponentList mComponentVector;
	};

	CLAIRE_NAMESPACE_END
}

#endif
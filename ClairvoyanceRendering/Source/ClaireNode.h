#ifndef CLAIRE_NODE_H
#define CLAIRE_NODE_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireNodeChain.h"

#include "ClaireQuaternion.h"
#include "ClaireVector.h"
#include "ClaireTransform.h"
#include "ClaireNameGenerator.h"
#include "Idiom\ClaireManager.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	using math::Quaternion;
	using math::Vector3;

	class CLAIRE_RENDERING_EXPORT Node
	{
		CLAIRE_MOVABLE_ONLY(Node)

		friend class NodeChain;
		friend class NodeChainTransformComponent;

	public:
		typedef std::unique_ptr<Node> NodeUPtr;
		typedef vector<Node*> NodeVector;

	public:
		Node(
			const string& name,
			const Transform& transform = Transform()
			);
		Node(
			const Transform& transform = Transform()
			);
		virtual ~Node(void);

		// Read only get
		Transform getTransform(void) const;
		// Read-write get
		Transform& getTransform(void);
		// Read only get
		// The derived transform is not valid until an update is called
		Transform getDerivedTransform(void) const;

		// Ensure that the derived transform has been updated
		void forceUpdateDerivedTransform(void) const;

		string getName(void) const { return mName; }
		NodeChain* getNodeChain(void) const { return mNodeChain.get(); }
		NodeVector getChildNodeVector(void) const { return mChildNodeVector; }
		NodeHandle getNodeHandle(void) const { return mHandle; }

		size_t getTreeSize(void) const;

		void update(void);

		Node* createChild(
			const string& name,
			const Transform& transform = Transform()
			);
		Node* createChild(
			const Transform& transform = Transform()
			);

		Node* attachChild(NodeUPtr child);
		NodeUPtr detachChild(const string& name);

	protected:
		virtual void update_(void) {}

		Node(
			NodeChainSPtr nodeChain,
			const string& name,
			const Transform& transform = Transform()
			);
		Node(
			NodeChainSPtr nodeChain,
			const Transform& transform = Transform()
			);

		virtual NodeUPtr create_(
			const string& name,
			const Transform& transform
			) CLAIRE_ABSTRACT;

	private:
		void setup(void);

		size_t getTreeSize_(size_t count) const;

		void createNodeChain(void);
		void addToChain(void);

		void setParent(Node* parent);

		void buildNodeChain(void);
		void buildNodeChain_(void);

		void setNodeChain(NodeChainSPtr nodeChain);

	protected:
		string mName;

		// Parent node
		Node* mParentNode;

		// Child nodes
		typedef OwningManager<Node, string> NodeManagerImpl;
		NodeManagerImpl mNodeManager;

		// Node list points to child nodes
		NodeVector mChildNodeVector;

		// Transform relative to local space
		Transform* mTransform;
		// Transform relative to global space
		Transform* mDerivedTransform;

		// Node chain shared among all children
		NodeChainSPtr mNodeChain;

	private:
		NodeHandle mHandle;

		Transform mInitialTransform;

		// Additional pass for updating the transform component
		// individually
		NodeChain::UpdatePass* mTransformPass;

		static NameGenerator sNameGenerator;
	};

	typedef Node::NodeUPtr NodeUPtr;

	CLAIRE_NAMESPACE_END
}

#endif
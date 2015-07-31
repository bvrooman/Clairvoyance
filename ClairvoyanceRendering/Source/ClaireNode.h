#ifndef CLAIRE_NODE_H
#define CLAIRE_NODE_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireNodeChain.h"
#include "ClaireTransform.h"
#include "Idiom\ClaireManager.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	using math::Quaternion;
	using math::Vector3;

	class CLAIRE_RENDERING_EXPORT Node
	{
		CLAIRE_MOVABLE_ONLY(Node)

	public:
		typedef std::unique_ptr<Node> NodeUPtr;
		typedef vector<Node*> NodeVector;

	public:
		Node(void) = default;
		virtual ~Node(void) = default;

		NodeHandle getHandle(void) const { return mHandle; }
		void setHandle(NodeHandle handle) { mHandle = handle; }

		// Read only get
		Transform getTransform(void) const;
		// Read-write get
		Transform& getTransform(void);
		// Read only get
		// The derived transform is not valid until an update is called
		Transform getDerivedTransform(void) const;

		void setTransformSource(Transform* const transform);
		void setDerivedTransformSource(Transform* const transform);

		void buildNodeChain(void);

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

		virtual NodeUPtr create_(
			const string& name,
			const Transform& transform
			) CLAIRE_ABSTRACT;

		virtual string generateName(void) CLAIRE_ABSTRACT;

		// Delegate ctor for root nodes
		Node(
			const string& name,
			const Transform& transform
			);

		// Delegate ctor for child nodes
		Node(
			NodeChainSPtr nodeChain,
			const string& name,
			const Transform& transform
			);

	private:
		size_t getTreeSize_(size_t count) const;

		void createNodeChain(void);
		void addToChain(void);

		void setParent(Node* parent);

		void buildNodeChain_(void);

		void setNodeChain(NodeChainSPtr nodeChain);

	protected:
		string mName;

		// Parent node
		Node* mParentNode = nullptr;

		// Child nodes
		typedef OwningManager<Node, string> NodeManagerImpl;
		NodeManagerImpl mNodeManager;

		// Node list points to child nodes
		NodeVector mChildNodeVector;

		// Transform relative to local space
		Transform* mTransform = nullptr;
		// Transform relative to global space
		Transform* mDerivedTransform = nullptr;

		// Node chain shared among all children
		NodeChainSPtr mNodeChain;

	private:
		NodeHandle mHandle = 0;

		Transform mInitialTransform;

		// Additional pass for updating the transform component
		// individually
		NodeChain::UpdatePass* mTransformPass;
	};

	typedef Node::NodeUPtr NodeUPtr;

	CLAIRE_NAMESPACE_END
}

#endif
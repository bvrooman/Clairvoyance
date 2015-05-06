#ifndef CLAIRE_SCENE_OBJECT_H
#define CLAIRE_SCENE_OBJECT_H

#include "ClaireRenderingPrerequisites.h"
#include "Memory\ClaireMemoryConfig.h"

#include "ClaireAxisAlignedBoundingBox.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	class SceneNode;

	class CLAIRE_RENDERING_EXPORT SceneObject
	{
	public:
		SceneObject(const string& name);
		virtual ~SceneObject(void);

		string getName(void) const { return mName; }

		void attachToSceneNode(SceneNode* sceneNode);
		SceneNode* getParentSceneNode(void) { return mParentSceneNode; }

		void calculateWorldAABB(void);
		AxisAlignedBoundingBox getWorldAABB(void) const { return mWorldAABB; }

	protected:
		virtual void calculateLocalAABB(void) CLAIRE_ABSTRACT;

	protected:
		string mName;

		SceneNode* mParentSceneNode = nullptr;

		AxisAlignedBoundingBox mLocalAABB;
		AxisAlignedBoundingBox mWorldAABB;
	};

	typedef std::unique_ptr<SceneObject> SceneObjectUPtr;

	CLAIRE_NAMESPACE_END
}

#endif
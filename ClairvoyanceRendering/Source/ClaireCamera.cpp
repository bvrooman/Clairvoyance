#include "ClaireCamera.h"

#include "ClaireScene.h"
#include "ClaireSceneNode.h"
#include "ClaireViewport.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	Camera::Camera(const string& name, Scene* Scene)
		: SceneObject(name)
		, mScene(Scene)
	{
		mLocalAABB.setExtents(
			Vector3::UNIT_SCALE * -1,
			Vector3::UNIT_SCALE
			);

		buildProjectionMatrix();
	}

	void Camera::renderScene(Viewport* viewport)
	{
		mScene->renderScene(this, viewport);
	}

	void Camera::setNearDistance(real nearDistance)
	{
		mViewFrustum.setNearDistance(nearDistance);
		buildProjectionMatrix();
	}

	void Camera::setFarDistance(real farDistance)
	{
		mViewFrustum.setFarDistance(farDistance);
		buildProjectionMatrix();
	}

	void Camera::setAspectRatio(real aspectRatio)
	{
		mViewFrustum.setAspectRatio(aspectRatio);
		buildProjectionMatrix();
	}

	void Camera::setFieldOfView(Radian fieldOfView)
	{
		mViewFrustum.setFieldOfViewY(fieldOfView);
		buildProjectionMatrix();
	}

	void Camera::buildProjectionMatrix(void)
	{
		mViewFrustum.buildProjectionMatrix();
	}

	void Camera::buildViewMatrix(void)
	{
		if(mParentSceneNode && 
			mCachedTransform != mParentSceneNode->getDerivedTransform())
		{
			mCachedTransform = mParentSceneNode->getDerivedTransform();
			mViewFrustum.buildViewMatrix(
				mCachedTransform.getRotationQuaternion(),
				mCachedTransform.getTranslation()
				);
		}
	}

	void Camera::calculateLocalAABB(void)
	{
		// Do nothing - local AABB should never change
	}

	CLAIRE_NAMESPACE_END
}
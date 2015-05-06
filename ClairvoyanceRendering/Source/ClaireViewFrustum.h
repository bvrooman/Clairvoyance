#ifndef CLAIRE_VIEW_FRUSTUM_H
#define CLAIRE_VIEW_FRUSTUM_H

#include "ClaireRenderingPrerequisites.h"
#include "Memory\ClaireMemoryConfig.h"

#include "ClairePlane.h"
#include "ClaireMatrix.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(math)
	class Quaternion;
	CLAIRE_NAMESPACE_END

	CLAIRE_NAMESPACE_BEGIN(rendering)

	using namespace math;

	enum FrustumPlane
	{
		FP_NEAR = 0,
		FP_FAR = 1,
		FP_LEFT = 2,
		FP_RIGHT = 3,
		FP_TOP = 4,
		FP_BOTTOM = 5
	};

	enum ProjectionType
	{
		PT_PERSPECTIVE,
		PT_ORTHOGRAPHIC
	};

	class CLAIRE_RENDERING_EXPORT ViewFrustum
		//: public GeneralAllocatedObject
	{
	private:
		struct ProjectionParameters
		{
			real left;
			real right;
			real bottom;
			real top;
		};

	public:
		ViewFrustum(void);
		~ViewFrustum(void);

		void setNearDistance(real nearDistance) { mNearDistance = nearDistance; }
		void setFarDistance(real farDistance) { mFarDistance = farDistance; }
		void setAspectRatio(real aspectRatio) { mAspectRatio = aspectRatio; }
		void setFieldOfViewY(Radian fovy) { mFieldOfViewY = fovy; }

		void buildProjectionMatrix(void);
		void buildViewMatrix(
			const Quaternion& orientation,
			const Vector3& position 
			);

	private:
		void updatePlanes(void);

	private:
		static ProjectionParameters calculateProjectionParameters(
			ProjectionType projectionType,
			real nearDistance,
			real aspectRatio,
			Radian fieldOfView
			);

	private:
		ProjectionType mProjectionType = PT_PERSPECTIVE;

		Plane mPlanes[6];

		// Used to build the projection matrix
		real mNearDistance = 1;
		real mFarDistance = 3000;
		real mAspectRatio = 4.0f / 3;
		Radian mFieldOfViewY = Radian(PI / 6);

		Matrix4 mProjectionMatrix = Matrix4::IDENTITY;
		Matrix4 mViewMatrix = Matrix4::IDENTITY;
	};

	CLAIRE_NAMESPACE_END
}

#endif
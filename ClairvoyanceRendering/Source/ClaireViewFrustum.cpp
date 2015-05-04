#include "ClaireViewFrustum.h"

#include "ClaireQuaternion.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	ViewFrustum::ViewFrustum(void)
		: mProjectionType(PT_PERSPECTIVE)
		, mNearDistance(1)
		, mFarDistance(3000)
		, mAspectRatio(4.0f / 3)
		, mFieldOfViewY(math::PI / 6)
		, mProjectionMatrix(Matrix4::IDENTITY)
		, mViewMatrix(Matrix4::IDENTITY)
	{
	}

	ViewFrustum::~ViewFrustum(void)
	{

	}

	void ViewFrustum::buildProjectionMatrix(void)
	{
		ViewFrustum::ProjectionParameters parameters = calculateProjectionParameters(
			mProjectionType,
			mNearDistance,
			mAspectRatio,
			mFieldOfViewY
			);

		if(mProjectionType == PT_PERSPECTIVE)
		{
			real invertedWidth = 1 / (parameters.right - parameters.left);
			real invertedHeight = 1 / (parameters.top - parameters.bottom);
			real invertedDepth = 1 / (mFarDistance - mNearDistance);

			real A = 2 * mNearDistance * invertedWidth;
			real B = 2 * mNearDistance * invertedHeight;
			real C = (parameters.right + parameters.left) * invertedWidth;
			real D = (parameters.top + parameters.bottom) * invertedHeight;
			real q, qn;

			q = -(mFarDistance + mNearDistance) * invertedDepth;
			qn = -2 * (mFarDistance * mNearDistance) * invertedDepth;

			// Right hand projection matrix
			// [ A 0 C 0  ]
			// [ 0 B D 0  ]
			// [ 0 0 q qn ]
			// [ 0 0 -1 0 ]

			mProjectionMatrix = Matrix4::ZERO;
			mProjectionMatrix[0][0] = A;
			mProjectionMatrix[0][2] = C;
			mProjectionMatrix[1][1] = B;
			mProjectionMatrix[1][2] = D;
			mProjectionMatrix[2][2] = q;
			mProjectionMatrix[2][3] = qn;
			mProjectionMatrix[3][2] = -1;
		}
		else
		{

		}
	}

	ViewFrustum::ProjectionParameters ViewFrustum::calculateProjectionParameters(
		ProjectionType projectionType,
		real nearDistance,
		real aspectRatio,
		Radian fieldOfView
		)
	{
		ProjectionParameters parameters;

		if(projectionType == PT_PERSPECTIVE)
		{
			Radian thetaY = fieldOfView / 2;
			real tanThetaY = math::tan(thetaY);
			real tanThetaX = tanThetaY * aspectRatio;

			real halfWidthNear = nearDistance * tanThetaX;
			real halfHeightNear = nearDistance * tanThetaY;

			parameters.left = -halfWidthNear;
			parameters.right = halfWidthNear;
			parameters.bottom = -halfHeightNear;
			parameters.top = halfHeightNear;
		}
		else
		{

		}

		return parameters;
	}

	void ViewFrustum::buildViewMatrix(
		const Quaternion& orientation,
		const Vector3& position
		)
	{
		Matrix3 rotation = orientation.asRotationMatrix();

		Matrix3 rotationT = rotation.transpose();
		Vector3 translation = -rotationT * position;

		mViewMatrix = Matrix4::IDENTITY;

		//Rotation
		mViewMatrix[0][0] = rotationT[0][0]; mViewMatrix[0][1] = rotationT[0][1]; mViewMatrix[0][2] = rotationT[0][2];
		mViewMatrix[1][0] = rotationT[1][0]; mViewMatrix[1][1] = rotationT[1][1]; mViewMatrix[1][2] = rotationT[1][2];
		mViewMatrix[2][0] = rotationT[2][0]; mViewMatrix[2][1] = rotationT[2][1]; mViewMatrix[2][2] = rotationT[2][2];

		//Translation
		mViewMatrix[0][3] = translation.x;
		mViewMatrix[1][3] = translation.y;
		mViewMatrix[2][3] = translation.z;
	}

	void ViewFrustum::updatePlanes(void)
	{
		Matrix4 viewProj = mProjectionMatrix * mViewMatrix;

		mPlanes[FP_LEFT].normal.x	 = viewProj[3][0] + viewProj[0][0];
		mPlanes[FP_LEFT].normal.y	 = viewProj[3][1] + viewProj[0][1];
		mPlanes[FP_LEFT].normal.z	 = viewProj[3][2] + viewProj[0][2];
		mPlanes[FP_LEFT].d			 = viewProj[3][3] + viewProj[0][3];

		mPlanes[FP_RIGHT].normal.x	 = viewProj[3][0] - viewProj[0][0];
		mPlanes[FP_RIGHT].normal.y	 = viewProj[3][1] - viewProj[0][1];
		mPlanes[FP_RIGHT].normal.z	 = viewProj[3][2] - viewProj[0][2];
		mPlanes[FP_RIGHT].d			 = viewProj[3][3] - viewProj[0][3];

		mPlanes[FP_TOP].normal.x	 = viewProj[3][0] - viewProj[1][0];
		mPlanes[FP_TOP].normal.y	 = viewProj[3][1] - viewProj[1][1];
		mPlanes[FP_TOP].normal.z	 = viewProj[3][2] - viewProj[1][2];
		mPlanes[FP_TOP].d			 = viewProj[3][3] - viewProj[1][3];

		mPlanes[FP_BOTTOM].normal.x	 = viewProj[3][0] + viewProj[1][0];
		mPlanes[FP_BOTTOM].normal.y	 = viewProj[3][1] + viewProj[1][1];
		mPlanes[FP_BOTTOM].normal.z	 = viewProj[3][2] + viewProj[1][2];
		mPlanes[FP_BOTTOM].d		 = viewProj[3][3] + viewProj[1][3];

		mPlanes[FP_NEAR].normal.x	 = viewProj[3][0] + viewProj[2][0];
		mPlanes[FP_NEAR].normal.y	 = viewProj[3][1] + viewProj[2][1];
		mPlanes[FP_NEAR].normal.z	 = viewProj[3][2] + viewProj[2][2];
		mPlanes[FP_NEAR].d			 = viewProj[3][3] + viewProj[2][3];

		mPlanes[FP_FAR].normal.x	 = viewProj[3][0] - viewProj[2][0];
		mPlanes[FP_FAR].normal.y	 = viewProj[3][1] - viewProj[2][1];
		mPlanes[FP_FAR].normal.z	 = viewProj[3][2] - viewProj[2][2];
		mPlanes[FP_FAR].d			 = viewProj[3][3] - viewProj[2][3];

		// Renormalize any normals which were not unit length
		for(int i = 0; i < 6; i++)
		{
			real length = mPlanes[i].normal.length();
			mPlanes[i].d /= length;
			mPlanes[i].normal.normalize();
		}
	}

	CLAIRE_NAMESPACE_END
}
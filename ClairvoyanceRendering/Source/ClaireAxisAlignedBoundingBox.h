#ifndef CLAIRE_AXIS_ALIGNED_BOUNDING_BOX_H
#define CLAIRE_AXIS_ALIGNED_BOUNDING_BOX_H

#include "ClaireRenderingPrerequisites.h"

#include "ClaireVector.h"
#include "ClaireTransform.h"

namespace Claire
{
	CLAIRE_NAMESPACE_BEGIN(rendering)

	using namespace math;

	class CLAIRE_RENDERING_EXPORT AxisAlignedBoundingBox
	{
	public:
		enum Definition
		{
			UNDEFINED,
			FINITE,
		};

	public:
		AxisAlignedBoundingBox(void)
			: mDefinition(UNDEFINED)
		{
			setExtents(Vector3::ZERO, Vector3::ZERO);
		}

		AxisAlignedBoundingBox(const Vector3& min, const Vector3& max)
			: mDefinition(FINITE)
		{
			setExtents(min, max);
		}

		inline void clear(void)
		{
			setExtents(Vector3::ZERO, Vector3::ZERO);
			mDefinition = UNDEFINED;
		}

		inline void setExtents(const Vector3& min, const Vector3& max)
		{
			setMinimum(min);
			setMaximum(max);
			mDefinition = FINITE;
		}

		inline void merge(const AxisAlignedBoundingBox& rhs)
		{
			switch (mDefinition)
			{
			case UNDEFINED:
				setExtents(
					rhs.mMinimum,
					rhs.mMaximum
					);
				break;
			case FINITE:
				includeMinimum(rhs.mMinimum);
				includeMaximum(rhs.mMaximum);
				break;
			}
		}

		/*
		Transform the box according to the transform supplied.
		The result is the axis aligned bounding box that surrounds
		the transformed extents. 
		*/
		inline void applyTransform(const Transform& transform)
		{
			assert(transform.isAffine());

			Vector3 centre = 0.5 * (mMaximum + mMinimum);
			Vector3 halfSize = 0.5 * (mMaximum - mMinimum);

			Quaternion r = transform.getRotationQuaternion();

			Vector3 centreDelta = r * centre + transform.getTranslation();
			Vector3 halfSizeDelta = r * halfSize;
			halfSizeDelta.toAbsolute();

			setExtents(
				centreDelta - halfSizeDelta,
				centreDelta + halfSizeDelta
				);
		}

		inline Vector3 getMinimum(void) const { return mMinimum; }
		inline Vector3 getMaximum(void) const { return mMaximum; }

		inline friend std::ostream& operator <<
			(std::ostream& o, const AxisAlignedBoundingBox& aabb)
		{
			o << "AABB( ";
			o << "Minimum " << aabb.mMinimum << " ; ";
			o << "Maximum " << aabb.mMaximum << " ";
			o << ")";
			return o;
		}

		bool operator == (const AxisAlignedBoundingBox& rhs) const
		{
			if(mMinimum == rhs.mMinimum && 
				mMaximum == rhs.mMaximum && 
				mDefinition == rhs.mDefinition)
			{
				return true;
			}
			return false;
		}

		bool operator != (const AxisAlignedBoundingBox& rhs) const
		{
			return *this == rhs;
		}

	private:
		inline void includeMinimum(const Vector3& rhs)
		{
			Vector3 min = mMinimum;

			// Find the most minimum components
			if (rhs.x < min.x)
			{
				min.x = rhs.x;
			}
			if (rhs.y < min.y)
			{
				min.y = rhs.y;
			}
			if (rhs.z < min.z)
			{
				min.z = rhs.z;
			}

			setMinimum(min);
		}

		inline void includeMaximum(const Vector3& rhs)
		{
			Vector3 max = mMaximum;

			// Find the most maximum components
			if (rhs.x > max.x)
			{
				max.x = rhs.x;
			}
			if (rhs.y > max.y)
			{
				max.y = rhs.y;
			}
			if (rhs.z > max.z)
			{
				max.z = rhs.z;
			}

			setMaximum(max);
		}

		inline void setMinimum(const Vector3& min)
		{
			mMinimum = min;
		}

		inline void setMaximum(const Vector3& max)
		{
			mMaximum = max;
		}

	private:
		Vector3 mMinimum;
		Vector3 mMaximum;
		Definition mDefinition;
	};
		
	CLAIRE_NAMESPACE_END
}

#endif
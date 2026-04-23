#pragma once
#include "Plane.hpp"
#include "Ray.hpp"
#include "UtilityFunctions.hpp"
#include "Sphere.hpp"
#include "AABB3D.hpp"

namespace CommonUtilities
{
	template<class T>
	bool IntersectionPlaneRay(const Plane<T>& aPlane, const Ray<T>& aRay, Vector3<T>& outIntersectionPoint);

	template<class T>
	bool IntersectionSphereAABB(const Sphere<T>& aSphere, const AABB3D<T>& aAABB3D, Vector3<T>& outIntersectionPoint);

	template<class T>
	bool IntersectionAABBRay(const AABB3D<T>& aAABB, const Ray<T>& aRay);

	template <class T>
	bool IntersectionSphereRay(const Sphere<T>& aSphere, const Ray<T>& aRay);


	template<class T>
	bool IntersectionPlaneRay(const Plane<T>& aPlane, const Ray<T>& aRay, Vector3<T>& outIntersectionPoint)
	{

		//	𝑡 =
		//  𝑑 − 𝑜 • 𝑛̂ / 
		//	𝑑̂ • 𝑛̂
		//	=
		//
		//D
		T valD = aPlane.GetPoint().Dot(aPlane.GetNormal());

		T valODotN = aRay.GetOrigin().Dot(aPlane.GetNormal());
		T valUp = valD - valODotN;

		T valDown = aRay.GetDirection().Dot(aPlane.GetNormal());

		if (valDown == 0)
		{
			T dotProd = aPlane.GetNormal().Dot(aPlane.GetPoint() - aRay.GetOrigin());
			if (dotProd == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		T valT = valUp / valDown;

		if (valT < 0)
		{
			return false;
		}
		else
		{
			Vector3<T> out = aRay.GetOrigin() + aRay.GetDirection() * valT;
			outIntersectionPoint = out;
			return true;
		}
	}

	template<class T>
	bool IntersectionSphereAABB(const Sphere<T>& aSphere, const AABB3D<T>& aAABB3D, Vector3<T>& outIntersectionPoint)
	{
		Vector3<T> closestPoint = aSphere.GetCenter();
		closestPoint.x = CommonUtilities::Clamp(closestPoint.x, aAABB3D.GetMin().x, aAABB3D.GetMax().x);
		closestPoint.y = CommonUtilities::Clamp(closestPoint.y, aAABB3D.GetMin().y, aAABB3D.GetMax().y);
		closestPoint.z = CommonUtilities::Clamp(closestPoint.z, aAABB3D.GetMin().z, aAABB3D.GetMax().z);

		T dist = pow((closestPoint.x - aSphere.GetCenter().x), T(2)) + pow((closestPoint.y - aSphere.GetCenter().y), T(2)) + pow((closestPoint.z - aSphere.GetCenter().z), T(2));
		if (dist <= pow(aSphere.GetRadius(),T(2)))
		{
			outIntersectionPoint = closestPoint;
			return true;
		}
		else
		{
			return false;
		}
	}

	template<class T>
	bool IntersectionAABBRay(const AABB3D<T>& aAABB, const Ray<T>& aRay)
	{
		T tMinX = (aAABB.GetMin().x - aRay.GetOrigin().x) / aRay.GetDirection().GetNormalized().x;
		T tMaxX = (aAABB.GetMax().x - aRay.GetOrigin().x) / aRay.GetDirection().GetNormalized().x;

		T tMinY = (aAABB.GetMin().y - aRay.GetOrigin().y) / aRay.GetDirection().GetNormalized().y;
		T tMaxY = (aAABB.GetMax().y - aRay.GetOrigin().y) / aRay.GetDirection().GetNormalized().y;

		T tMinZ = (aAABB.GetMin().z - aRay.GetOrigin().z) / aRay.GetDirection().GetNormalized().z;
		T tMaxZ = (aAABB.GetMax().z - aRay.GetOrigin().z) / aRay.GetDirection().GetNormalized().z;

		CommonUtilities::Vector3<T> px1 = aRay.GetOrigin() + aRay.GetDirection().GetNormalized() * tMinX;
		CommonUtilities::Vector3<T> px2 = aRay.GetOrigin() + aRay.GetDirection().GetNormalized() * tMaxX;

		if (tMinX >= 0)
		{
			if (aAABB.IsInside(px1))
			{
				return true;
			}
		}
		if (tMaxX >= 0)
		{
			if (aAABB.IsInside(px2))
			{
				return true;
			}
		}

		CommonUtilities::Vector3<T> py1 = aRay.GetOrigin() + aRay.GetDirection().GetNormalized() * tMinY;
		CommonUtilities::Vector3<T> py2 = aRay.GetOrigin() + aRay.GetDirection().GetNormalized() * tMaxY;

		if (tMinY >= 0)
		{
			if (aAABB.IsInside(py1))
			{
				return true;
			}
		}
		if (tMaxY >= 0)
		{
			if (aAABB.IsInside(py2))
			{
				return true;
			}
		}

		CommonUtilities::Vector3<T> pz1 = aRay.GetOrigin() + aRay.GetDirection().GetNormalized() * tMinZ;
		CommonUtilities::Vector3<T> pz2 = aRay.GetOrigin() + aRay.GetDirection().GetNormalized() * tMaxZ;

		if (tMinZ >= 0)
		{
			if (aAABB.IsInside(pz1))
			{
				return true;
			}
		}
		if (tMaxZ >= 0)
		{
			if (aAABB.IsInside(pz2))
			{
				return true;
			}
		}

		return false;
	}

	template<class T>
	bool IntersectionSphereRay(const Sphere<T>& aSphere, const Ray<T>& aRay)
	{
		Vector3<T> valSphereNegRay = aSphere.GetCenter() - aRay.GetOrigin() ;
		Vector3<T> rayDirNormalised = aRay.GetDirection().GetNormalized();
		T projDot = (rayDirNormalised.Dot(valSphereNegRay));
		if (projDot < 0)
		{
			return false;
		}
		Vector3<T> proj = projDot * rayDirNormalised;
		Vector3<T> projNegOrig = aRay.GetOrigin() + proj;

		T projDist = pow((projNegOrig.x-aSphere.GetCenter().x), T(2)) + pow((projNegOrig.y - aSphere.GetCenter().y), T(2)) + pow((projNegOrig.z - aSphere.GetCenter().z), T(2));

		if (projDist <= pow(aSphere.GetRadius(),T(2)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}
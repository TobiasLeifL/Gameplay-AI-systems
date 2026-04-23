#pragma once
#include "vector.hpp"
#include "Plane.hpp"
#include <vector>

namespace CommonUtilities
{
	template<class T>
	class PlaneVolume
	{
	public:
		PlaneVolume();
		PlaneVolume(const std::vector<Plane<T>>& aPlaneList);

		void AddPlane(const Plane<T>& aPlane);

		bool IsInside(const Vector3<T>& aPosition) const;

		std::vector<Plane<T>>& GetPlanes();

	private:
		std::vector<Plane<T>> myPlanes;
	};

	template<class T>
	inline PlaneVolume<T>::PlaneVolume()
	{

	}

	template<class T>
	inline PlaneVolume<T>::PlaneVolume(const std::vector<Plane<T>>& aPlaneList)
	{
		myPlanes = aPlaneList;
	}

	template<class T>
	inline void PlaneVolume<T>::AddPlane(const Plane<T>& aPlane)
	{
		myPlanes.push_back(aPlane);
	}
	template<class T>
	inline bool PlaneVolume<T>::IsInside(const Vector3<T>& aPosition) const
	{

		bool isInside = true;
		for (int i = 0; i < myPlanes.size(); i++)
		{
			T DotProduct = myPlanes[i].GetDotProductOnPlane(aPosition);
			if (DotProduct > 0)
			{
				isInside = false;
				break;
			}
		}
		return isInside;
	}

	template<class T>
	inline std::vector<Plane<T>>& PlaneVolume<T>::GetPlanes()
	{
		return myPlanes;
	}
}
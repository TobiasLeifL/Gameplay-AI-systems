#pragma once
#include "Vector.hpp"

namespace CommonUtilities
{
	template<class T>
	class Sphere
	{
		public:
			Sphere();
			Sphere(const Sphere<T>& aSphere) = default;
			Sphere(const Vector3<T>& aCenter, T aRadius);
			~Sphere();

			void InitWithCenterAndRadius(const Vector3<T>& aCenter, T aRadius);

			bool IsInside(const Vector3<T>& aPosition) const;
	
			const Vector3<T>&  GetCenter() const;
			const T& GetRadius() const;

		private:
			Vector3<T> myCenter;
			T myRadius;
	};

	template<class T>
	inline Sphere<T>::Sphere()
	{
		myCenter = Vector3<T>(0, 0, 0);
		myRadius = 0;
	}

	template<class T>
	inline Sphere<T>::Sphere(const Vector3<T>& aCenter, T aRadius)
	{
		myCenter = aCenter;
		myRadius = aRadius;
	}

	template<class T>
	inline Sphere<T>::~Sphere()
	{

	}

	template<class T>
	inline void Sphere<T>::InitWithCenterAndRadius(const Vector3<T>& aCenter, T aRadius)
	{
		myCenter = aCenter;
		myRadius = aRadius;
	}

	template<class T>
	inline bool Sphere<T>::IsInside(const Vector3<T>& aPosition) const
	{
		T calc = static_cast<T> (pow((aPosition.x-myCenter.x), 2) + pow((aPosition.y-myCenter.y), 2) + pow((aPosition.z-myCenter.z), 2));
		T radCalc = static_cast<T>(pow(myRadius, 2));
		if (calc <= radCalc)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template<class T>
	inline const Vector3<T>& Sphere<T>::GetCenter() const
	{
		return myCenter;
	}

	template<class T>
	inline const T& Sphere<T>::GetRadius() const
	{
		return myRadius;
	}

}
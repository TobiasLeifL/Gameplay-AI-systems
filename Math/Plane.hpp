#pragma once
#include "Vector.hpp"

namespace CommonUtilities
{
	template<class T>
	class Plane
	{
		public:
			Plane();
			Plane(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2);
			Plane(const Vector3<T>& aPoint0, const Vector3<T>& aNormal);

			void InitWith3Points(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2);
			void InitWithPointAndNormal(const Vector3<T>& aPoint0, const Vector3<T>& aNormal);

			bool IsInside(const Vector3<T>& aPosition) const;
			T GetDotProductOnPlane(const CommonUtilities::Vector3<T>& aPosition) const;

			const Vector3<T>& GetNormal() const;

			const Vector3<T>& GetPoint() const;

		private:
			//vars
			Vector3<T> myPoint;
			Vector3<T> myNormal;
	};

	template<class T>
	inline Plane<T>::Plane()
	{
		myPoint = Vector3<T>(0, 0, 0);
		myNormal = Vector3<T>(0, 0, 0);
	}

	template<class T>
	inline Plane<T>::Plane(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2)
	{
		myPoint = aPoint0;
		Vector3<T> myDirection0 = aPoint1 - aPoint0;
		Vector3<T> myDirection1 = aPoint2 - aPoint0;
		myNormal = myDirection0.Cross(myDirection1);
		myNormal.Normalize();
	}

	template<class T>
	inline Plane<T>::Plane(const Vector3<T>& aPoint0, const Vector3<T>& aNormal)
	{
		myPoint = aPoint0;
		myNormal = aNormal;
	}

	template<class T>
	inline void Plane<T>::InitWith3Points(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2)
	{
		myPoint = aPoint0;
		Vector3<T> myDirection0 = aPoint1 - aPoint0;
		Vector3<T> myDirection1 = aPoint2 - aPoint0;
		myNormal = myDirection0.Cross(myDirection1);
		myNormal.Normalize();
	}

	template<class T>
	inline void Plane<T>::InitWithPointAndNormal(const Vector3<T>& aPoint0, const Vector3<T>& aNormal)
	{
		myPoint = aPoint0;
		myNormal = aNormal;
	}

	template<class T>
	inline bool Plane<T>::IsInside(const Vector3<T>& aPosition) const
	{
		Vector3<T> sub = aPosition - myPoint;
		T product = GetNormal().Dot(sub);
		if (product <= 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template<class T>
	inline T Plane<T>::GetDotProductOnPlane(const CommonUtilities::Vector3<T>& aPosition) const
	{
		Vector3<T> sub = aPosition - myPoint;
		T product = GetNormal().Dot(sub);
		return product;
	}

	template<class T>
	inline const Vector3<T>& Plane<T>::GetNormal() const
	{
		return myNormal;
	}

	template<class T>
	inline const Vector3<T>& Plane<T>::GetPoint() const
	{
		return myPoint;
	}

}
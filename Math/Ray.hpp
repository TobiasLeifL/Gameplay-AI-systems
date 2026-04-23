#pragma once
#include "Vector.hpp"

namespace CommonUtilities
{
	template <class T>
	class Ray
	{
		public:
			Ray();
			Ray(const Ray<T>& aRay) = default;
			Ray(const Vector3<T>& aOrigin, const Vector3<T>& aDirection);

			~Ray();

			void InitWith2Points(const Vector3<T>& aOrigin, const Vector3<T>& aPoint);

			void InitWithOriginAndDirection(const Vector3<T>& aOrigin, const Vector3<T>& aDirection);

			const Vector3<T>& GetDirection() const;
			const Vector3<T>& GetOrigin() const;

		private:
			Vector3<T> myOrigin;
			Vector3<T> myDirection;
	};

	template<class T>
	inline Ray<T>::Ray()
	{
		myOrigin = Vector3<T>{ 0,0,0 };
		myDirection = Vector3<T>{ 0,0,0 };
	}

	template<class T>
	inline Ray<T>::Ray(const Vector3<T>& aOrigin, const Vector3<T>& aDirection)
	{
		myOrigin = aOrigin;
		myDirection = aDirection;
	}

	template<class T>
	inline Ray<T>::~Ray()
	{

	}

	template<class T>
	inline void Ray<T>::InitWith2Points(const Vector3<T>& aOrigin, const Vector3<T>& aPoint)
	{
		myOrigin = aOrigin;
		Vector3<T> newDir = aPoint - aOrigin;
		myDirection = newDir;
	}

	template<class T>
	inline void Ray<T>::InitWithOriginAndDirection(const Vector3<T>& aOrigin, const Vector3<T>& aDirection)
	{
		myOrigin = aOrigin;
		myDirection = aDirection;
	}
	template<class T>
	inline const Vector3<T>& Ray<T>::GetDirection() const
	{
		return myDirection;
	}
	template<class T>
	inline const Vector3<T>& Ray<T>::GetOrigin() const
	{
		return myOrigin;
	}
}
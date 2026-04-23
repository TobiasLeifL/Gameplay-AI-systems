#pragma once
#include "vector.hpp"

namespace CommonUtilities
{
	template<class T>
	class Line
	{
		public:
			Line();

			Line(const Line<T>& aLine) = default;

			Line(const CommonUtilities::Vector2<T>& aPoint0, const CommonUtilities::Vector2<T>& aPoint1);

			void InitWith2Points(const CommonUtilities::Vector2<T>& aPoint0, const Vector2<T>& aPoint1);

			void InitWithPointAndDirection(const Vector2<T>& aPoint, const Vector2<T>& aDirection);

			bool IsInside(const CommonUtilities::Vector2<T>& aPosition) const;
			T GetDotProductOnLine(const CommonUtilities::Vector2<T>& aPosition) const;

			const Vector2<T>& GetDirection() const;
			const Vector2<T> GetNormal() const;
			const Vector2<T>& GetPoint() const;
			
		private:
			//Vars
			CommonUtilities::Vector2<T> myDirection;
			CommonUtilities::Vector2<T> myPoint;
	};

	template<class T>
	inline Line<T>::Line()
	{
		myDirection = Vector2<T>(0, 0);
		myPoint = Vector2<T>(0, 0);
	}

	template<class T>
	inline Line<T>::Line(const CommonUtilities::Vector2<T>& aPoint0, const CommonUtilities::Vector2<T>& aPoint1)
	{
		myDirection = aPoint1 - aPoint0;
		myPoint = aPoint0;
	}

	template<class T>
	inline void Line<T>::InitWith2Points(const CommonUtilities::Vector2<T>& aPoint0, const Vector2<T>& aPoint1)
	{
		myDirection = aPoint1 - aPoint0;
		myPoint = aPoint0;
	}

	template<class T>
	inline void Line<T>::InitWithPointAndDirection(const Vector2<T>& aPoint, const Vector2<T>& aDirection)
	{
		myDirection = aDirection;
		myPoint = aPoint;
	}

	template<class T>
	inline bool Line<T>::IsInside(const CommonUtilities::Vector2<T>& aPosition) const
	{
		Vector2<T> sub = aPosition - myPoint;
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
	inline T Line<T>::GetDotProductOnLine(const CommonUtilities::Vector2<T>& aPosition) const
	{
		Vector2<T> sub = aPosition - myPoint;
		Vector2<T> norm = GetNormal();
		T product = norm.Dot(sub);
		return product;
	}

	template<class T>
	inline const Vector2<T>& Line<T>::GetDirection() const
	{
		return myDirection;
	}

	template<class T>
	inline const Vector2<T> Line<T>::GetNormal() const
	{
		return Vector2<T>(-myDirection.y, myDirection.x);
	}
	template<class T>
	inline const Vector2<T>& Line<T>::GetPoint() const
	{
		return myPoint;
	}
}
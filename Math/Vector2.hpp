#pragma once

namespace CommonUtilities
{
	template <class T>
	class Vector2
	{
		public:
			Vector2<T>();
			Vector2<T>(const T& anX, const T& anY);
			Vector2<T>(const Vector2<T>& anotherVector) = default;

			~Vector2<T>() = default;

			Vector2<T>& operator = (const Vector2<T>& anotherVector2) = default;

			template <class OtherVectorClass>
			explicit operator OtherVectorClass() const;

			Vector2<T> operator- () const;
			Vector2<T> operator / (const T t);

			T LengthSqr() const;
			T Length() const;
			Vector2 <T> GetNormalized() const;

			void Normalize();

			T Dot(const Vector2<T>& anotherVector) const;

			T x;
			T y;
		private:

	};

	template <class T>
	template <class OtherVectorClass>
	inline Vector2<T>::operator OtherVectorClass() const;

	template <class T>
	Vector2<T> operator + (const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		Vector2<T> newVector;
		newVector.x = aVector0.x + aVector1.x;
		newVector.y = aVector0.y + aVector1.y;
		return newVector;
	}

	template<class T>
	Vector2<T> operator - (const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		Vector2<T> newVector;
		newVector.x = aVector0.x - aVector1.x;
		newVector.y = aVector0.y - aVector1.y;
		return newVector;
	}

	template <class T>
	Vector2<T> operator * (const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		Vector2<T> newVector;
		newVector.x = aVector0.x * aVector1.x;
		newVector.y = aVector0.y * aVector1.y;
		return newVector;
	}

	template <class T>
	Vector2<T> operator * (const Vector2<T>& aVector, const T& aScalar)
	{
		Vector2<T> newVector = aVector;
		newVector.x = newVector.x * aScalar;
		newVector.y = newVector.y * aScalar;
		return newVector;
	}

	template <class T>
	Vector2<T> operator * (const T& aScalar , const Vector2<T>& aVector)
	{
		Vector2<T> newVector = aVector;
		newVector.x = newVector.x * aScalar;
		newVector.y = newVector.y * aScalar;
		return newVector;
	}

	template <class T>
	Vector2<T> operator / (const Vector2<T>& aVector, const T& aScalar)
	{
		Vector2<T> newVector = aVector;
		newVector.x = newVector.x / aScalar;
		newVector.y = newVector.y / aScalar;
		return newVector;
	}

	template<class T>
	void operator += (Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0 = aVector0 + aVector1;
	}

	template <class T>
	void operator -= (Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0 = aVector0 - aVector1;
	}

	template <class T>
	void operator *= (Vector2<T>& aVector0, const T& aScalar)
	{
		aVector0 = aVector0 * aScalar;
	}

	template<class T>
	void operator /= (Vector2<T>& aVector0, const T& aScalar)
	{
		aVector0 = aVector0 / aScalar;
	}

	template<class T>
	inline Vector2<T>::Vector2() : x(T(0)) , y(T(0))
	{

	}

	template<class T>
	inline Vector2<T>::Vector2(const T& anX, const T& anY)
	{
		x = anX;
		y = anY;
	}

	template<class T>
	template<class OtherVectorClass>
	inline Vector2<T>::operator OtherVectorClass() const
	{
		return OtherVectorClass(x, y);
	}
	template<class T>
	inline Vector2<T> Vector2<T>::operator/(const T t)
	{
		Vector2<T> newVector = *this;
		newVector.x = newVector.x / t;
		newVector.y = newVector.y / t;
		return newVector;
	}
	template<class T>
	inline Vector2<T> Vector2<T>::operator-() const
	{
		Vector2<T> newVector = *this;
		newVector.x = -newVector.x;
		newVector.y = -newVector.y;
		return newVector;
	}
	template<class T>
	inline T Vector2<T>::LengthSqr() const
	{
		T newT = x*x + y*y;
		return newT;
	}
	template<class T>
	inline T Vector2<T>::Length() const
	{ 
		T newT = static_cast<T>(sqrt(pow(x, T(2)) + pow(y, T(2)) ));
		return newT;
	}
	template<class T>
	inline Vector2<T> Vector2<T>::GetNormalized() const
	{
		Vector2<T> newVector = *this;
		newVector = newVector / Length();
		return newVector;
	}
	template<class T>
	inline void Vector2<T>::Normalize()
	{
		T l = Length();
		x = x / l;
		y = y / l;
	}

	template<class T>
	inline T Vector2<T>::Dot(const Vector2<T>& anotherVector) const
	{
		T t = (x * anotherVector.x) + (y * anotherVector.y);
		return t;
	}

}
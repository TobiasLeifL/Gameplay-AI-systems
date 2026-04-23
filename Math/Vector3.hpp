#pragma once

namespace CommonUtilities
{
	template <class T>
	class Vector3
	{
	public:
		Vector3<T>();
		Vector3<T>(const T& anX, const T& anY, const T& anZ);
		Vector3<T>(const Vector3<T>& anotherVector) = default;

		~Vector3<T>() = default;

		Vector3<T>& operator = (const Vector3<T>& anotherVector3) = default;

		template <class OtherVectorClass>
		explicit operator OtherVectorClass() const;

		Vector3<T> operator- () const;
		Vector3<T> operator / (const T t);

		T LengthSqr() const;
		T Length() const;
		Vector3 <T> GetNormalized() const;

		void Normalize();

		T Dot(const Vector3<T>& anotherVector) const;

		T x;
		T y;
		T z;

		Vector3<T> Cross(const Vector3<T>& aVector) const;

	private:

	};

	template <class T>
	template <class OtherVectorClass>
	inline Vector3<T>::operator OtherVectorClass() const;

	template <class T>
	Vector3<T> operator + (const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		Vector3<T> newVector;
		newVector.x = aVector0.x + aVector1.x;
		newVector.y = aVector0.y + aVector1.y;
		newVector.z = aVector0.z + aVector1.z;
		return newVector;
	}

	template<class T>
	Vector3<T> operator - (const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		Vector3<T> newVector;
		newVector.x = aVector0.x - aVector1.x;
		newVector.y = aVector0.y - aVector1.y;
		newVector.z = aVector0.z - aVector1.z;
		return newVector;
	}

	template <class T>
	Vector3<T> operator * (const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		Vector3<T> newVector;
		newVector.x = aVector0.x * aVector1.x;
		newVector.y = aVector0.y * aVector1.y;
		newVector.z = aVector0.z * aVector1.z;
		return newVector;
	}

	template <class T>
	Vector3<T> operator * (const Vector3<T>& aVector, const T& aScalar)
	{
		Vector3<T> newVector = aVector;
		newVector.x = newVector.x * aScalar;
		newVector.y = newVector.y * aScalar;
		newVector.z = newVector.z * aScalar;
		return newVector;
	}

	template <class T>
	Vector3<T> operator * (const T& aScalar , const Vector3<T>& aVector)
	{
		Vector3<T> newVector = aVector;
		newVector.x = newVector.x * aScalar;
		newVector.y = newVector.y * aScalar;
		newVector.z = newVector.z * aScalar;
		return newVector;
	}

	template <class T>
	Vector3<T> operator / (const Vector3<T>& aVector, const T& aScalar)
	{
		Vector3<T> newVector = aVector;
		newVector.x = newVector.x / aScalar;
		newVector.y = newVector.y / aScalar;
		newVector.z = newVector.z / aScalar;
		return newVector;
	}

	template<class T>
	void operator += (Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0 = aVector0 + aVector1;
	}

	template <class T>
	void operator -= (Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0 = aVector0 - aVector1;
	}

	template <class T>
	void operator *= (Vector3<T>& aVector0, const T& aScalar)
	{
		aVector0 = aVector0 * aScalar;
	}

	template<class T>
	void operator /= (Vector3<T>& aVector0, const T& aScalar)
	{
		aVector0 = aVector0 / aScalar;
	}

	template<class T>
	inline Vector3<T>::Vector3() : x(T(0)), y(T(0)) , z(T(0))
	{

	}

	template<class T>
	inline Vector3<T>::Vector3(const T& anX, const T& anY , const T& anZ)
	{
		x = anX;
		y = anY;
		z = anZ;
	}

	template<class T>
	template<class OtherVectorClass>
	inline Vector3<T>::operator OtherVectorClass() const
	{
		return OtherVectorClass(x, y , z);
	}
	template<class T>
	inline Vector3<T> Vector3<T>::operator / (const T t)
	{
		Vector3<T> newVector = *this;
		newVector.x = newVector.x / t;
		newVector.y = newVector.y / t;
		newVector.z = newVector.z / t;
		return newVector;
	}
	template<class T>
	inline Vector3<T> Vector3<T>::operator-() const
	{
		Vector3<T> newVector = *this;
		newVector.x = -newVector.x;
		newVector.y = -newVector.y;
		newVector.z = -newVector.z;
		return newVector;
	}
	template<class T>
	inline T Vector3<T>::LengthSqr() const
	{
		T newT = x * x + y * y + z * z;
		return newT;
	}
	template<class T>
	inline T Vector3<T>::Length() const
	{
		T newT = static_cast<T>(sqrt(pow(x, T(2)) + pow(y, T(2)) + pow(z,T(2))));
		return newT;
	}
	template<class T>
	inline Vector3<T> Vector3<T>::GetNormalized() const
	{
		Vector3<T> newVector = *this;
		newVector = newVector / Length();
		return newVector;
	}
	template<class T>
	inline void Vector3<T>::Normalize()
	{
		T l = Length();
		x = x / l;
		y = y / l;
		z = z / l;
	}

	template<class T>
	inline T Vector3<T>::Dot(const Vector3<T>& anotherVector) const
	{
		T t = (x * anotherVector.x) + (y * anotherVector.y) + (z * anotherVector.z);
		return t;
	}

	template<class T>
	inline Vector3<T> Vector3<T>::Cross(const Vector3<T>& aVector) const
	{
		Vector3<T> newVector = *this;
		newVector.x = (y * aVector.z) - (z * aVector.y);
		newVector.y = (z * aVector.x) - (x * aVector.z);
		newVector.z = (x * aVector.y) - (y * aVector.x);
		return newVector;
	}

}
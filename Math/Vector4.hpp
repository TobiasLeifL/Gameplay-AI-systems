#pragma once

namespace CommonUtilities
{
	template <class T>
	class Vector4
	{
	public:
		Vector4<T>();
		Vector4<T>(const T& anX, const T& anY, const T& anZ , const T& anW);
		Vector4<T>(const Vector4<T>& anotherVector) = default;

		~Vector4<T>() = default;

		Vector4<T>& operator = (const Vector4<T>& anotherVector4) = default;

		template <class OtherVectorClass>
		explicit operator OtherVectorClass() const;

		Vector4<T> operator- () const;
		Vector4<T> operator / (const T t);

		T LengthSqr() const;
		T Length() const;
		Vector4 <T> GetNormalized() const;

		void Normalize();

		T Dot(const Vector4<T>& anotherVector) const;

		T x;
		T y;
		T z;
		T w;

	private:

	};

	template <class T>
	template <class OtherVectorClass>
	inline Vector4<T>::operator OtherVectorClass() const;

	template <class T>
	Vector4<T> operator + (const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		Vector4<T> newVector;
		newVector.x = aVector0.x + aVector1.x;
		newVector.y = aVector0.y + aVector1.y;
		newVector.z = aVector0.z + aVector1.z;
		newVector.w = aVector0.w + aVector1.w;
		return newVector;
	}

	template<class T>
	Vector4<T> operator - (const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		Vector4<T> newVector;
		newVector.x = aVector0.x - aVector1.x;
		newVector.y = aVector0.y - aVector1.y;
		newVector.z = aVector0.z - aVector1.z;
		newVector.w = aVector0.w - aVector1.w;
		return newVector;
	}

	template <class T>
	Vector4<T> operator * (const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		Vector4<T> newVector;
		newVector.x = aVector0.x * aVector1.x;
		newVector.y = aVector0.y * aVector1.y;
		newVector.z = aVector0.z * aVector1.z;
		newVector.w = aVector0.w * aVector1.w;
		return newVector;
	}

	template <class T>
	Vector4<T> operator * (const Vector4<T>& aVector, const T& aScalar)
	{
		Vector4<T> newVector = aVector;
		newVector.x = newVector.x * aScalar;
		newVector.y = newVector.y * aScalar;
		newVector.z = newVector.z * aScalar;
		newVector.w = newVector.w * aScalar;
		return newVector;
	}

	template <class T>
	Vector4<T> operator * (const T& aScalar , const Vector4<T>& aVector)
	{
		Vector4<T> newVector = aVector;
		newVector.x = newVector.x * aScalar;
		newVector.y = newVector.y * aScalar;
		newVector.z = newVector.z * aScalar;
		newVector.w = newVector.w * aScalar;
		return newVector;
	}

	template <class T>
	Vector4<T> operator / (const Vector4<T>& aVector, const T& aScalar)
	{
		Vector4<T> newVector = aVector;
		newVector.x = newVector.x / aScalar;
		newVector.y = newVector.y / aScalar;
		newVector.z = newVector.z / aScalar;
		newVector.w = newVector.w / aScalar;
		return newVector;
	}

	template<class T>
	void operator += (Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0 = aVector0 + aVector1;
	}

	template <class T>
	void operator -= (Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0 = aVector0 - aVector1;
	}

	template <class T>
	void operator *= (Vector4<T>& aVector0, const T& aScalar)
	{
		aVector0 = aVector0 * aScalar;
	}

	template<class T>
	void operator /= (Vector4<T>& aVector0, const T& aScalar)
	{
		aVector0 = aVector0 / aScalar;
	}

	template<class T>
	inline Vector4<T>::Vector4() : x(T(0)), y(T(0)), z(T(0)) , w(T(0))
	{

	}

	template<class T>
	inline Vector4<T>::Vector4(const T& anX, const T& anY, const T& anZ , const T& anW)
	{
		x = anX;
		y = anY;
		z = anZ;
		w = anW;
	}

	template<class T>
	template<class OtherVectorClass>
	inline Vector4<T>::operator OtherVectorClass() const
	{
		return OtherVectorClass(x, y, z , w);
	}
	template<class T>
	inline Vector4<T> Vector4<T>::operator / (const T t)
	{
		Vector4<T> newVector = *this;
		newVector.x = newVector.x / t;
		newVector.y = newVector.y / t;
		newVector.z = newVector.z / t;
		newVector.w = newVector.w / t;
		return newVector;
	}
	template<class T>
	inline Vector4<T> Vector4<T>::operator-() const
	{
		Vector4<T> newVector = *this;
		newVector.x = -newVector.x;
		newVector.y = -newVector.y;
		newVector.z = -newVector.z;
		newVector.w = -newVector.w;
		return newVector;
	}
	template<class T>
	inline T Vector4<T>::LengthSqr() const
	{
		T newT = x * x + y * y + z * z + w * w;
		return newT;
	}
	template<class T>
	inline T Vector4<T>::Length() const
	{
		T newT = static_cast<T>(sqrt(pow(x, T(2)) + pow(y, T(2)) + pow(z, T(2)) + pow(w,T(2))));
		return newT;
	}
	template<class T>
	inline Vector4<T> Vector4<T>::GetNormalized() const
	{
		Vector4<T> newVector = *this;
		newVector = newVector / Length();
		return newVector;
	}
	template<class T>
	inline void Vector4<T>::Normalize()
	{
		T l = Length();
		x = x / l;
		y = y / l;
		z = z / l;
		w = w / l;
	}

	template<class T>
	inline T Vector4<T>::Dot(const Vector4<T>& anotherVector) const
	{
		T t = (x * anotherVector.x) + (y * anotherVector.y) + (z * anotherVector.z) + (w*anotherVector.w);
		return t;
	}

}
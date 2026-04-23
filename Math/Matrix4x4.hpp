#pragma once
#include <array>
#include "Vector.hpp"

namespace CommonUtilities
{
	template<class T>
	class Matrix4x4
	{
		public:
			Matrix4x4<T>();
			Matrix4x4<T>(const Matrix4x4<T>& aMatrix) = default;

			T& operator() (const int aRow, const int aColumn);
			const T& operator() (const int aRow, const int aColumn) const;

			~Matrix4x4() = default;

			Matrix4x4<T> GetTranspose() const;

			Matrix4x4<T> GetFastInverse() const;

			static Matrix4x4<T> CreateRotationAroundX(const T anAngleInRadians);
			static Matrix4x4<T> CreateRotationAroundY(const T anAngleInRadians);
			static Matrix4x4<T> CreateRotationAroundZ(const T anAngleInRadians);

			Matrix4x4<T>& operator=(const Matrix4x4<T>& anotherMatrix) = default;

			CommonUtilities::Vector4<T> GetUp();
			CommonUtilities::Vector4<T> GetRight();
			CommonUtilities::Vector4<T> GetForward();

		private:
			std::array <std::array<T, 4>, 4> myData;
	};

	template<class T>
	inline Matrix4x4<T>::Matrix4x4()
	{
		std::array<std::array<T, 4>, 4> aNewData
		{
			{
				{1,0,0,0},
				{0,1,0,0},
				{0,0,1,0},
				{0,0,0,1}
			}
		};
		myData = aNewData;
	}

	template <class T>
	inline Matrix4x4<T> Matrix4x4<T>::GetFastInverse() const
	{
		Matrix4x4<T> newMatrixR;
		Matrix4x4<T> newMatrixT;

		newMatrixT.myData =
		{ {
			{1,0,0,0},
			{0,1,0,0},
			{0,0,1,0},
			{-(*this)(4,1),-(*this)(4,2),-(*this)(4,3),1}
		} };

		newMatrixR = (*this).GetTranspose();

		Matrix4x4<T> newMatrix = newMatrixT * newMatrixR;
		newMatrix(1, 4) = 0;
		newMatrix(2, 4) = 0;
		newMatrix(3, 4) = 0;
		newMatrix(4, 4) = 1;

		return newMatrix;
	}

	template<class T>
	inline T& Matrix4x4<T>::operator()(const int aRow, const int aColumn)
	{
		return myData[aRow - 1][aColumn - 1];
	}

	template<class T>
	inline const T& Matrix4x4<T>::operator()(const int aRow, const int aColumn) const
	{
		return myData[aRow - 1][aColumn - 1];
	}

	template<class T>
	inline Matrix4x4<T> Matrix4x4<T>::GetTranspose() const
	{
		Matrix4x4<T> newMatrix;
		newMatrix.myData =
		{ {
			{(*this)(1,1),(*this)(2,1),(*this)(3,1),(*this)(4,1)},
			{(*this)(1,2),(*this)(2,2),(*this)(3,2),(*this)(4,2)},
			{(*this)(1,3),(*this)(2,3),(*this)(3,3),(*this)(4,3)},
			{(*this)(1,4),(*this)(2,4),(*this)(3,4),(*this)(4,4)}
		} };

		return newMatrix;

	}

	template<class T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundX(const T anAngleInRadians)
	{
		Matrix4x4<T> newMatrix;

		newMatrix(2, 2) = cos(anAngleInRadians);
		newMatrix(2, 3) = sin(anAngleInRadians);
		newMatrix(3, 2) = -sin(anAngleInRadians);
		newMatrix(3, 3) = cos(anAngleInRadians);

		return newMatrix;
	}

	template<class T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundY(const T anAngleInRadians)
	{
		Matrix4x4<T> newMatrix;

		newMatrix(1, 1) = static_cast<T>(cos(anAngleInRadians));
		newMatrix(1, 3) = static_cast<T>( - sin(anAngleInRadians));
		newMatrix(3, 1) = static_cast<T>(sin(anAngleInRadians));
		newMatrix(3, 3) = static_cast<T>(cos(anAngleInRadians));

		return newMatrix;
	}

	template<class T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundZ(const T anAngleInRadians)
	{
		Matrix4x4<T> newMatrix;

		newMatrix(1, 1) = cos(anAngleInRadians);
		newMatrix(1, 2) = sin(anAngleInRadians);
		newMatrix(2, 1) = -sin(anAngleInRadians);
		newMatrix(2, 2) = cos(anAngleInRadians);

		return newMatrix;
	}

	template<class T>
	inline CommonUtilities::Vector4<T> Matrix4x4<T>::GetUp()
	{
		CommonUtilities::Vector4<T> newVector = { (*this)(2,1),(*this)(2,2),(*this)(2,3),(*this)(2,4) };
		return newVector;
	}

	template<class T>
	inline CommonUtilities::Vector4<T> Matrix4x4<T>::GetRight()
	{
		CommonUtilities::Vector4<T> newVector = { (*this)(1,1),(*this)(1,2),(*this)(1,3),(*this)(1,4) };
		return newVector;
	}

	template<class T>
	inline CommonUtilities::Vector4<T> Matrix4x4<T>::GetForward()
	{
		CommonUtilities::Vector4<T> newVector = { (*this)(3,1),(*this)(3,2),(*this)(3,3),(*this)(3,4) };
		return newVector;
	}

	template<class T>
	Matrix4x4<T> operator*(const Matrix4x4<T>& aMatrix , const Matrix4x4<T>& anotherMatrix)
	{
		Matrix4x4<T> productMatrix;
		productMatrix(1, 1) = (aMatrix(1, 1) * anotherMatrix(1, 1)) + (aMatrix(1, 2) * anotherMatrix(2, 1)) + (aMatrix(1, 3) * anotherMatrix(3, 1)) + (aMatrix(1, 4) * anotherMatrix(4, 1));
		productMatrix(1, 2) = (aMatrix(1, 1) * anotherMatrix(1, 2)) + (aMatrix(1, 2) * anotherMatrix(2, 2)) + (aMatrix(1, 3) * anotherMatrix(3, 2)) + (aMatrix(1, 4) * anotherMatrix(4, 2));
		productMatrix(1, 3) = (aMatrix(1, 1) * anotherMatrix(1, 3)) + (aMatrix(1, 2) * anotherMatrix(2, 3)) + (aMatrix(1, 3) * anotherMatrix(3, 3)) + (aMatrix(1, 4) * anotherMatrix(4, 3));
		productMatrix(1, 4) = (aMatrix(1, 1) * anotherMatrix(1, 4)) + (aMatrix(1, 2) * anotherMatrix(2, 4)) + (aMatrix(1, 3) * anotherMatrix(3, 4)) + (aMatrix(1, 4) * anotherMatrix(4, 4));

		productMatrix(2, 1) = (aMatrix(2, 1) * anotherMatrix(1, 1)) + (aMatrix(2, 2) * anotherMatrix(2, 1)) + (aMatrix(2, 3) * anotherMatrix(3, 1)) + (aMatrix(2, 4) * anotherMatrix(4, 1));
		productMatrix(2, 2) = (aMatrix(2, 1) * anotherMatrix(1, 2)) + (aMatrix(2, 2) * anotherMatrix(2, 2)) + (aMatrix(2, 3) * anotherMatrix(3, 2)) + (aMatrix(2, 4) * anotherMatrix(4, 2));
		productMatrix(2, 3) = (aMatrix(2, 1) * anotherMatrix(1, 3)) + (aMatrix(2, 2) * anotherMatrix(2, 3)) + (aMatrix(2, 3) * anotherMatrix(3, 3)) + (aMatrix(2, 4) * anotherMatrix(4, 3));
		productMatrix(2, 4) = (aMatrix(2, 1) * anotherMatrix(1, 4)) + (aMatrix(2, 2) * anotherMatrix(2, 4)) + (aMatrix(2, 3) * anotherMatrix(3, 4)) + (aMatrix(2, 4) * anotherMatrix(4, 4));

		productMatrix(3, 1) = (aMatrix(3, 1) * anotherMatrix(1, 1)) + (aMatrix(3, 2) * anotherMatrix(2, 1)) + (aMatrix(3, 3) * anotherMatrix(3, 1)) + (aMatrix(3, 4) * anotherMatrix(4, 1));
		productMatrix(3, 2) = (aMatrix(3, 1) * anotherMatrix(1, 2)) + (aMatrix(3, 2) * anotherMatrix(2, 2)) + (aMatrix(3, 3) * anotherMatrix(3, 2)) + (aMatrix(3, 4) * anotherMatrix(4, 2));
		productMatrix(3, 3) = (aMatrix(3, 1) * anotherMatrix(1, 3)) + (aMatrix(3, 2) * anotherMatrix(2, 3)) + (aMatrix(3, 3) * anotherMatrix(3, 3)) + (aMatrix(3, 4) * anotherMatrix(4, 3));
		productMatrix(3, 4) = (aMatrix(3, 1) * anotherMatrix(1, 4)) + (aMatrix(3, 2) * anotherMatrix(2, 4)) + (aMatrix(3, 3) * anotherMatrix(3, 4)) + (aMatrix(3, 4) * anotherMatrix(4, 4));

		productMatrix(4, 1) = (aMatrix(4, 1) * anotherMatrix(1, 1)) + (aMatrix(4, 2) * anotherMatrix(2, 1)) + (aMatrix(4, 3) * anotherMatrix(3, 1)) + (aMatrix(4, 4) * anotherMatrix(4, 1));
		productMatrix(4, 2) = (aMatrix(4, 1) * anotherMatrix(1, 2)) + (aMatrix(4, 2) * anotherMatrix(2, 2)) + (aMatrix(4, 3) * anotherMatrix(3, 2)) + (aMatrix(4, 4) * anotherMatrix(4, 2));
		productMatrix(4, 3) = (aMatrix(4, 1) * anotherMatrix(1, 3)) + (aMatrix(4, 2) * anotherMatrix(2, 3)) + (aMatrix(4, 3) * anotherMatrix(3, 3)) + (aMatrix(4, 4) * anotherMatrix(4, 3));
		productMatrix(4, 4) = (aMatrix(4, 1) * anotherMatrix(1, 4)) + (aMatrix(4, 2) * anotherMatrix(2, 4)) + (aMatrix(4, 3) * anotherMatrix(3, 4)) + (aMatrix(4, 4) * anotherMatrix(4, 4));

		return productMatrix;
		
		//Old one , 
		/*
		Matrix4x4<T> aNewMatrix(aMatrix);
		for (int i = 1; i < 5; i++)
		{
			for (int j = 1; j < 5; j++)
			{
				T value = 0;
				for (int ev = 1; ev < 5; ev++)
				{
					T newVal = aMatrix(i, ev) * anotherMatrix.operator()(ev, j);
					value = value + newVal;
				}
				aNewMatrix(i, j) = value;
			}
		}
		return aNewMatrix;
		*/
	}

	template<class T>
	void operator*=(Matrix4x4<T>& aMatrix , const Matrix4x4<T>& anotherMatrix)
	{
		aMatrix = aMatrix * anotherMatrix;
	}

	template<class T>
	Vector4<T> operator*(const Vector4<T>& aVector , const Matrix4x4<T>& aMatrix)
	{
		Vector4<T> aNewVector;
		aNewVector.x = (aVector.x * aMatrix(1, 1)) + (aVector.y * aMatrix(2, 1)) + (aVector.z * aMatrix(3, 1)) + (aVector.w * aMatrix(4, 1));
		aNewVector.y = (aVector.x * aMatrix(1, 2)) + (aVector.y * aMatrix(2, 2)) + (aVector.z * aMatrix(3, 2)) + (aVector.w * aMatrix(4, 2));
		aNewVector.z = (aVector.x * aMatrix(1, 3)) + (aVector.y * aMatrix(2, 3)) + (aVector.z * aMatrix(3, 3)) + (aVector.w * aMatrix(4, 3));
		aNewVector.w = (aVector.x * aMatrix(1, 4)) + (aVector.y * aMatrix(2, 4)) + (aVector.z * aMatrix(3, 4)) + (aVector.w * aMatrix(4, 4));
		return aNewVector;
	}

	template<class T>
	Matrix4x4<T> operator+(const Matrix4x4<T>& aMatrix , const Matrix4x4<T>& anotherMatrix)
	{
		Matrix4x4<T> newMatrix  (aMatrix);
		for (int i = 1; i < 5; i++)
		{
			for (int j = 1; j < 5; j++)
			{
				newMatrix(i, j) = newMatrix(i, j) + anotherMatrix(i, j);
			}
		}
		return newMatrix;
	}
	template<class T>
	void operator+=(Matrix4x4<T>& aMatrix , const Matrix4x4<T>& anotherMatrix)
	{
		Matrix4x4<T> newMatrix(aMatrix);
		for (int i = 1; i < 5; i++)
		{
			for (int j = 1; j < 5; j++)
			{
				newMatrix(i, j) = newMatrix(i, j) + anotherMatrix(i, j);
			}
		}
		aMatrix = newMatrix;
	}
	template<class T>
	Matrix4x4<T> operator-(const Matrix4x4<T>& aMatrix , const Matrix4x4<T>& anotherMatrix)
	{
		Matrix4x4<T> newMatrix(aMatrix);
		for (int i = 1; i < 5; i++)
		{
			for (int j = 1; j < 5; j++)
			{
				newMatrix(i, j) = newMatrix(i, j) - anotherMatrix(i, j);
			}
		}
		return newMatrix;
	}
	template<class T>
	void operator-=(Matrix4x4<T>& aMatrix , const Matrix4x4<T>& anotherMatrix)
	{
		Matrix4x4<T> newMatrix(aMatrix);
		for (int i = 1; i < 5; i++)
		{
			for (int j = 1; j < 5; j++)
			{
				newMatrix(i, j) = newMatrix(i, j) - anotherMatrix(i, j);
			}
		}
		aMatrix = newMatrix;
	}
	template<class T>
	bool operator==(const Matrix4x4<T>& aMatrix , const Matrix4x4<T>& anotherMatrix)
	{
		for (int i = 1; i < 5; i++)
		{
			for (int j = 1; j < 5; j++)
			{
				if (aMatrix(i, j) != anotherMatrix.operator()(i, j))
				{
					return false;
				}
			}
		}
		return true;
	}
}
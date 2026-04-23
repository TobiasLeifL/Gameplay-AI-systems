#pragma once
#include <array>
#include "Vector.hpp"
#include "Matrix4x4.hpp"

namespace CommonUtilities
{
	template<class T>
	class Matrix3x3
	{
		public:
			Matrix3x3<T>();
			Matrix3x3<T>(const Matrix3x3<T>& aMatrix) = default;
			Matrix3x3<T>(const Matrix4x4<T>& aMatrix);

			~Matrix3x3() = default;

			T& operator() (const int aRow, const int aColumn);
			const T& operator() (const int aRow, const int aColumn) const;

			Matrix3x3<T> GetTranspose() const;

			static Matrix3x3<T> CreateRotationAroundX(const T anAngleInRadians);
			static Matrix3x3<T> CreateRotationAroundY(const T anAngleInRadians);
			static Matrix3x3<T> CreateRotationAroundZ(const T anAngleInRadians);

			Matrix3x3<T>& operator = (const Matrix3x3<T>& anotherMatrix) = default;

		private:
			std::array <std::array<T, 3>, 3> myData;
	};

	template<class T>
	inline Matrix3x3<T>::Matrix3x3()
	{
		std::array<std::array<T, 3>, 3> aNewData
		{
			{
				{1,0,0},
				{0,1,0},
				{0,0,1}
			}
		};
		myData = aNewData;
	}

	template<class T>
	inline Matrix3x3<T>::Matrix3x3(const Matrix4x4<T>& aMatrix)
	{
		Matrix3x3<T> aNewMatrix;
		for (int i = 1; i < 4; i++)
		{
			for (int j = 1; j < 4; j++)
			{
				aNewMatrix(i, j) = aMatrix(i, j);
			}
		}
		(*this) =  aNewMatrix;
	}

	template<class T>
	inline T& Matrix3x3<T>::operator()(const int aRow, const int aColumn)
	{
		return myData[aRow - 1][aColumn - 1];
	}
	template<class T>
	inline const T& Matrix3x3<T>::operator()(const int aRow, const int aColumn) const
	{
		return myData[aRow - 1][aColumn - 1];
	}
	template<class T>
	inline Matrix3x3<T> Matrix3x3<T>::GetTranspose() const
	{
		Matrix3x3<T> newMatrix;
		newMatrix.myData =
		{ {
			{(*this)(1,1),(*this)(2,1),(*this)(3,1)},
			{(*this)(1,2),(*this)(2,2),(*this)(3,2)},
			{(*this)(1,3),(*this)(2,3),(*this)(3,3)}
		} };

		return newMatrix;
	}

	template<class T>
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundX(const T anAngleInRadians)
	{
		Matrix3x3<T> newMatrix;
		newMatrix.myData =
		{ {
			{1,0,0},
			{0,cos(anAngleInRadians),sin(anAngleInRadians)},
			{0,-sin(anAngleInRadians),cos(anAngleInRadians)}
		} };

		return newMatrix;
	}

	template<class T>
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundY(const T anAngleInRadians)
	{
		Matrix3x3<T> newMatrix;
		newMatrix.myData =
		{ {
			{cos(anAngleInRadians),0,-sin(anAngleInRadians)},
			{0,1,0},
			{sin(anAngleInRadians),0,cos(anAngleInRadians)}
		} };

		return newMatrix;
	}

	template<class T>
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundZ(const T anAngleInRadians)
	{
		Matrix3x3<T> newMatrix;
		newMatrix.myData =
		{ {
			{cos(anAngleInRadians),sin(anAngleInRadians),0},
			{-sin(anAngleInRadians),cos(anAngleInRadians),0},
			{0,0,1}
		} };

		return newMatrix;
	}

	template<class T>
	Matrix3x3<T> operator* (const Matrix3x3<T>& aMatrix ,const Matrix3x3<T>& anotherMatrix)
	{
		Matrix3x3<T> aNewMatrix(aMatrix);
		for (int i = 1; i < 4; i++)
		{
			for (int j = 1; j < 4; j++)
			{
				T value = 0;
				for (int ev = 1; ev < 4; ev++)
				{
					T newVal = aMatrix(i, ev) * anotherMatrix.operator()(ev, j);
					value = value + newVal;
				}
				aNewMatrix.operator()(i, j) = value;
			}
		}
		return aNewMatrix;
	}

	template<class T>
	void operator*= (Matrix3x3<T>& aMatrix , const Matrix3x3<T>& anotherMatrix)
	{

		Matrix3x3<T> productMatrix;
		productMatrix(1, 1) = (aMatrix(1, 1) * anotherMatrix(1, 1)) + (aMatrix(1, 2) * anotherMatrix(2, 1)) + (aMatrix(1, 3) * anotherMatrix(3, 1));
		productMatrix(1, 2) = (aMatrix(1, 1) * anotherMatrix(1, 2)) + (aMatrix(1, 2) * anotherMatrix(2, 2)) + (aMatrix(1, 3) * anotherMatrix(3, 2));
		productMatrix(1, 3) = (aMatrix(1, 1) * anotherMatrix(1, 3)) + (aMatrix(1, 2) * anotherMatrix(2, 3)) + (aMatrix(1, 3) * anotherMatrix(3, 3));

		productMatrix(2, 1) = (aMatrix(2, 1) * anotherMatrix(1, 1)) + (aMatrix(2, 2) * anotherMatrix(2, 1)) + (aMatrix(2, 3) * anotherMatrix(3, 1));
		productMatrix(2, 2) = (aMatrix(2, 1) * anotherMatrix(1, 2)) + (aMatrix(2, 2) * anotherMatrix(2, 2)) + (aMatrix(2, 3) * anotherMatrix(3, 2));
		productMatrix(2, 3) = (aMatrix(2, 1) * anotherMatrix(1, 3)) + (aMatrix(2, 2) * anotherMatrix(2, 3)) + (aMatrix(2, 3) * anotherMatrix(3, 3));

		productMatrix(3, 1) = (aMatrix(3, 1) * anotherMatrix(1, 1)) + (aMatrix(3, 2) * anotherMatrix(2, 1)) + (aMatrix(3, 3) * anotherMatrix(3, 1));
		productMatrix(3, 2) = (aMatrix(3, 1) * anotherMatrix(1, 2)) + (aMatrix(3, 2) * anotherMatrix(2, 2)) + (aMatrix(3, 3) * anotherMatrix(3, 2));
		productMatrix(3, 3) = (aMatrix(3, 1) * anotherMatrix(1, 3)) + (aMatrix(3, 2) * anotherMatrix(2, 3)) + (aMatrix(3, 3) * anotherMatrix(3, 3));


		return productMatrix;

		//Old version
		/*
		Matrix3x3<T> aNewMatrix(aMatrix);
		for (int i = 1; i < 4; i++)
		{
			for (int j = 1; j < 4; j++)
			{
				T value = 0;
				for (int ev = 1; ev < 4; ev++)
				{
					T newVal = aMatrix(i, ev) * anotherMatrix(ev, j);
					value = value + newVal;
				}
				aNewMatrix(i, j) = value;
			}
		}
		aMatrix = aNewMatrix;
		*/
	}

	template<class T>
	Vector3<T> operator * (const Vector3<T>& aVector ,const Matrix3x3<T>& aMatrix)
	{
		Vector3<T> aNewVector;
		aNewVector.x = (aVector.x * aMatrix(1, 1)) + (aVector.y * aMatrix(2, 1)) + (aVector.z * aMatrix(3, 1));
		aNewVector.y = (aVector.x * aMatrix(1, 2)) + (aVector.y * aMatrix(2, 2)) + (aVector.z * aMatrix(3, 2));
		aNewVector.z = (aVector.x * aMatrix(1, 3)) + (aVector.y * aMatrix(2, 3)) + (aVector.z * aMatrix(3, 3));
		return aNewVector;
	}

	template<class T>
	Matrix3x3<T> operator + (const Matrix3x3<T>& aMatrix , const Matrix3x3<T>& anotherMatrix)
	{
		Matrix3x3<T> newMatrix(aMatrix);
		for (int i = 1; i < 4; i++)
		{
			for (int j = 1; j < 4; j++)
			{
				newMatrix(i, j) = aMatrix(i, j) + anotherMatrix.operator()(i, j);
			}
		}
		return newMatrix;
	}

	template<class T>
	void operator += (Matrix3x3<T>& aMatrix , const Matrix3x3<T>& anotherMatrix)
	{
		for (int i = 1; i < 4; i++)
		{
			for (int j = 1; j < 4; j++)
			{
				aMatrix(i, j) = aMatrix(i, j) + anotherMatrix.operator()(i, j);
			}
		}
	}

	template<class T>
	Matrix3x3<T> operator - (const Matrix3x3<T>& aMatrix , const Matrix3x3<T>& anotherMatrix)
	{
		Matrix3x3<T> newMatrix(aMatrix);
		for (int i = 1; i < 4; i++)
		{
			for (int j = 1; j < 4; j++)
			{
				newMatrix.operator()(i, j) = newMatrix.operator()(i, j) - anotherMatrix.operator()(i, j);
			}
		}
		return newMatrix;
	}

	template<class T>
	void operator -= (Matrix3x3<T>& aMatrix , const Matrix3x3<T>& anotherMatrix)
	{
		for (int i = 1; i < 4; i++)
		{
			for (int j = 1; j < 4; j++)
			{
				aMatrix(i, j) = aMatrix(i, j) - anotherMatrix.operator()(i, j);
			}
		}
	}

	template<class T>
	bool operator == (const Matrix3x3<T>& aMatrix , const Matrix3x3<T>& anotherMatrix)
	{
		for (int i = 1; i < 4; i++)
		{
			for (int j = 1; j < 4; j++)
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
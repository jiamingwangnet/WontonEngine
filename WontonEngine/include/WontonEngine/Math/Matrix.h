#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include "Vector.h"

namespace won
{
	namespace priv
	{
		template<glm::length_t C, glm::length_t R, class T>
		class Matrix
		{
		public:
			// if there is one value of 1, give an identity matrix
			Matrix(std::initializer_list<T> values); // do checking if there are enough values (C * R)
			Matrix(glm::mat<C, R, T, glm::packed_highp> matrix); // do checking if there are enough values (C * R)

			Matrix<C, R, T> operator+(const Matrix<C, R, T>& mat) const;
			Matrix<C, R, T> operator-(const Matrix<C, R, T>& mat) const;
			Matrix<C, R, T> operator*(const Matrix<C, R, T>& mat) const;
			Matrix<C, R, T> operator/(const Matrix<C, R, T>& mat) const;

			Matrix<C, R, T>& operator*(const T& scalar) const;

			Matrix<C, R, T>& operator+=(const Matrix<C, R, T>& mat);
			Matrix<C, R, T>& operator-=(const Matrix<C, R, T>& mat);
			Matrix<C, R, T>& operator*=(const Matrix<C, R, T>& mat);
			Matrix<C, R, T>& operator/=(const Matrix<C, R, T>& mat);

			Matrix<C, R, T>& operator*=(const T& scalar);

			glm::vec<R, T, glm::packed_highp>& operator[](int index);
			const glm::vec<R, T, glm::packed_highp>& operator[](int index) const;

			explicit operator glm::mat<C, R, T, glm::packed_highp>() const;

			Matrix<R, C, T> Transposed() const;

		private:
			glm::mat<C, R, T, glm::packed_highp> matrix;
		};

		template<glm::length_t C, glm::length_t R, class T>
		inline Matrix<C, R, T>::Matrix(glm::mat<C, R, T, glm::packed_highp> matrix)
			: matrix{ matrix }
		{}
		template<glm::length_t C, glm::length_t R, class T>
		inline Matrix<C, R, T> Matrix<C, R, T>::operator+(const Matrix<C, R, T>& mat) const
		{
			return Matrix<C, R, T>{matrix + mat.matrix};
		}
		template<glm::length_t C, glm::length_t R, class T>
		inline Matrix<C, R, T> Matrix<C, R, T>::operator-(const Matrix<C, R, T>& mat) const
		{
			return Matrix<C, R, T>{matrix - mat.matrix};
		}
		template<glm::length_t C, glm::length_t R, class T> // FIXME:
		inline Matrix<C, R, T> Matrix<C, R, T>::operator*(const Matrix<C, R, T>& mat) const
		{
			return Matrix<C, R, T>{matrix * mat.matrix};
		}
		template<glm::length_t C, glm::length_t R, class T>
		inline Matrix<C, R, T> Matrix<C, R, T>::operator/(const Matrix<C, R, T>& mat) const
		{
			return Matrix<C, R, T>{matrix / mat.matrix};
		}
		template<glm::length_t C, glm::length_t R, class T>
		inline Matrix<C, R, T>& Matrix<C, R, T>::operator*(const T& scalar) const
		{
			return Matrix<C, R, T>{matrix * scalar};
		}
		template<glm::length_t C, glm::length_t R, class T>
		inline Matrix<C, R, T>& Matrix<C, R, T>::operator+=(const Matrix<C, R, T>& mat)
		{
			matrix += mat.matrix;
			return *this;
		}
		template<glm::length_t C, glm::length_t R, class T>
		inline Matrix<C, R, T>& Matrix<C, R, T>::operator-=(const Matrix<C, R, T>& mat)
		{
			matrix -= mat.matrix;
			return *this;
		}

		template<glm::length_t C, glm::length_t R, class T>
		inline Matrix<C, R, T>& Matrix<C, R, T>::operator*=(const Matrix<C, R, T>& mat)
		{
			matrix *= mat.matrix;
			return *this;
		}

		template<glm::length_t C, glm::length_t R, class T>
		inline Matrix<C, R, T>& Matrix<C, R, T>::operator/=(const Matrix<C, R, T>& mat)
		{
			matrix /= mat.matrix;
			return *this;
		}

		template<glm::length_t C, glm::length_t R, class T>
		inline Matrix<C, R, T>& Matrix<C, R, T>::operator*=(const T& scalar)
		{
			matrix *= scalar;
			return *this;
		}

		template<glm::length_t C, glm::length_t R, class T>
		inline Matrix<C, R, T>::operator glm::mat<C, R, T, glm::packed_highp>() const
		{
			return matrix;
		}
	}
}

template<glm::length_t C, glm::length_t R, class T>
inline won::priv::Matrix<C, R, T>::Matrix(std::initializer_list<T> values)
{
	if (values.size() == 1 && *values.begin() == (T)1.0f)
	{
		matrix = glm::mat<C, R, T, glm::packed_highp>{(T)1.0f};
		return;
	}

	if (values.size() != (std::size_t)C * (std::size_t)R)
		Error::ThrowError("Incorrect number of values for Matrix.", std::cout, __LINE__, __FILE__);

	for (int i = 0; i < (int)R; i++)
	{
		for (int j = 0; j < (int)C; j++)
		{
			matrix[i][j] = *(values.begin() + (i * (int)C + j));
		}
	}
}

template<glm::length_t C, glm::length_t R, class T>
inline glm::vec<R, T, glm::packed_highp>& won::priv::Matrix<C, R, T>::operator[](int index)
{
	return matrix[index];
}

template<glm::length_t C, glm::length_t R, class T>
inline const glm::vec<R, T, glm::packed_highp>& won::priv::Matrix<C, R, T>::operator[](int index) const
{
	return matrix[index];
}

template<glm::length_t C, glm::length_t R, class T>
inline won::priv::Matrix<R, C, T> won::priv::Matrix<C, R, T>::Transposed() const
{
	return glm::transpose(matrix);
}

namespace won {
	using Matrix2x2 = priv::Matrix<2, 2, glm::f32>;
	using Matrix3x3 = priv::Matrix<3, 3, glm::f32>;
	using Matrix4x4 = priv::Matrix<4, 4, glm::f32>;
}
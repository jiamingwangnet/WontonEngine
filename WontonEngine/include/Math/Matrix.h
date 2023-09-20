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

			Matrix<C, R, T> operator+(const Matrix<C, R, T>& vec) const;
			Matrix<C, R, T> operator-(const Matrix<C, R, T>& vec) const;
			Matrix<C, R, T> operator*(const Matrix<C, R, T>& vec) const;
			Matrix<C, R, T> operator/(const Matrix<C, R, T>& vec) const;

			Matrix<C, R, T>& operator*(const T& scalar) const;

			Matrix<C, R, T>& operator+=(const Matrix<C, R, T>& vec);
			Matrix<C, R, T>& operator-=(const Matrix<C, R, T>& vec);
			Matrix<C, R, T>& operator*=(const Matrix<C, R, T>& vec);
			Matrix<C, R, T>& operator/=(const Matrix<C, R, T>& vec);

			Matrix<C, R, T>& operator*=(const T& scalar);

			priv::Vector<R, T>& operator[](std::size_t index);
			const priv::Vector<R, T>& operator[](std::size_t index) const;

			explicit operator glm::mat<C, R, T, glm::packed_highp>() const;

			Matrix<R, C, T> Transposed() const;

		private:
			glm::mat<C, R, T, glm::packed_highp> matrix;
		};
	}

	using Matrix2x2 = priv::Matrix<2, 2, glm::f32>;
	using Matrix3x3 = priv::Matrix<3, 3, glm::f32>;
	using Matrix4x4 = priv::Matrix<4, 4, glm::f32>;
}
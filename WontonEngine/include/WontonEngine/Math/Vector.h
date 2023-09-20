#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <initializer_list>
#include <stdexcept>

namespace won
{
	namespace priv
	{
		template<glm::length_t L, class T>
		class Vector
		{
		public:
			Vector(std::initializer_list<T> values); // do checking if there are enough values
			Vector(glm::vec<L, T, glm::packed_highp> vector); // conversion from glm::vec

			Vector<L, T> operator+(const Vector<L, T>& vec) const;
			Vector<L, T> operator-(const Vector<L, T>& vec) const;
			Vector<L, T> operator*(const Vector<L, T>& vec) const; // component by component multiplication. NOT DOT PRODUCT
			Vector<L, T> operator/(const Vector<L, T>& vec) const;

			Vector<L, T>& operator*(const T& scalar) const;

			Vector<L, T>& operator+=(const Vector<L, T>& vec);
			Vector<L, T>& operator-=(const Vector<L, T>& vec);
			Vector<L, T>& operator*=(const Vector<L, T>& vec); // component by component multiplication. NOT DOT PRODUCT
			Vector<L, T>& operator/=(const Vector<L, T>& vec);

			Vector<L, T>& operator*=(const T& scalar);

			static T Dot(const Vector<L, T>& lhs, const Vector<L, T>& rhs);
			static Vector<3, T> Cross(const Vector<3, T>& lhs, const Vector<3, T>& rhs);
			static T Distance(const Vector<3, T>& lhs, const Vector<3, T>& rhs);

			T& operator[](std::size_t index);
			const T& operator[](std::size_t index) const;

			explicit operator glm::vec<L, T, glm::packed_highp>() const;

			Vector<L, T> Normalized() const;
			float Magnitude() const;

		private:
			glm::vec<L, T, glm::packed_highp> vector;
		};

		template<glm::length_t L, class T>
		inline Vector<L, T>::Vector(std::initializer_list<T> values)
		{
			if (values.size() > (std::size_t)L || values.size() < (std::size_t)L)
				throw std::exception{ "ERROR: Incorrect number of values for Vector" };

			for (glm::length_t i = 0; i < L; i++)
			{
				vector[i] = *(values.begin() + i);
			}
		}

		template<glm::length_t L, class T>
		inline Vector<L, T>::Vector(glm::vec<L, T, glm::packed_highp> vector)
			: vector{vector}
		{}
		template<glm::length_t L, class T>
		inline T& Vector<L, T>::operator[](std::size_t index)
		{
			return vector[index];
		}
		template<glm::length_t L, class T>
		inline const T& Vector<L, T>::operator[](std::size_t index) const
		{
			return vector[index];
		}
	}

	using Vector1 = priv::Vector<1, float>;
	using Vector2 = priv::Vector<2, float>;
	using Vector3 = priv::Vector<3, float>;
	using Vector4 = priv::Vector<4, float>;
}
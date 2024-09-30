#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/norm.hpp>
#include <initializer_list>
#include <stdexcept>
#include "../Error.h"
#include <iostream>

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
			Vector() = default;

			Vector<L, T> operator+(const Vector<L, T>& vec) const;
			Vector<L, T> operator-(const Vector<L, T>& vec) const;
			Vector<L, T> operator*(const Vector<L, T>& vec) const; // component by component multiplication. NOT DOT PRODUCT
			Vector<L, T> operator/(const Vector<L, T>& vec) const;

			Vector<L, T> operator*(const T& scalar) const;

			Vector<L, T>& operator+=(const Vector<L, T>& vec);
			Vector<L, T>& operator-=(const Vector<L, T>& vec);
			Vector<L, T>& operator*=(const Vector<L, T>& vec); // component by component multiplication. NOT DOT PRODUCT
			Vector<L, T>& operator/=(const Vector<L, T>& vec);

			Vector<L, T>& operator*=(const T& scalar);

			static T Dot(const Vector<L, T>& lhs, const Vector<L, T>& rhs);
			static Vector<3, T> Cross(const Vector<3, T>& lhs, const Vector<3, T>& rhs);
			static T Distance(const Vector<3, T>& lhs, const Vector<3, T>& rhs);

			T& operator[](int index);
			const T& operator[](int index) const;

			explicit operator glm::vec<L, T, glm::packed_highp>() const;

			Vector<L, T> Normalized() const;
			float Magnitude() const;
			float Magnitude2() const; // magnitude squared

			T& x();
			T& y();
			T& z();
			T& w();

			const T& x() const;
			const T& y() const;
			const T& z() const;
			const T& w() const;

		private:
			glm::vec<L, T, glm::packed_highp> vector;
		};

		template<glm::length_t L, class T>
		inline Vector<L, T>::Vector(std::initializer_list<T> values)
		{
			if (values.size() != (std::size_t)L)
				Error::ThrowError("Incorrect number of values for Vector.", std::cout, __LINE__, __FILE__);

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
		inline Vector<L, T> Vector<L, T>::operator+(const Vector<L, T>&vec) const
		{
			return Vector<L, T>{vector + vec.vector};
		}

		template<glm::length_t L, class T>
		inline Vector<L, T> Vector<L, T>::operator-(const Vector<L, T>& vec) const
		{
			return Vector<L, T>{vector - vec.vector};
		}

		template<glm::length_t L, class T>
		inline Vector<L, T> Vector<L, T>::operator*(const Vector<L, T>& vec) const
		{
			return Vector<L, T>{vector * vec.vector};
		}

		template<glm::length_t L, class T>
		inline Vector<L, T> Vector<L, T>::operator/(const Vector<L, T>& vec) const
		{
			return Vector<L, T>{vector / vec.vector};
		}

		template<glm::length_t L, class T>
		inline Vector<L, T> Vector<L, T>::operator*(const T& scalar) const
		{
			return Vector<L, T>(vector * scalar);
		}

		template<glm::length_t L, class T>
		inline Vector<L, T>& Vector<L, T>::operator+=(const Vector<L, T>& vec)
		{
			vector += vec.vector;
			return *this;
		}

		template<glm::length_t L, class T>
		inline Vector<L, T>& Vector<L, T>::operator-=(const Vector<L, T>& vec)
		{
			vector -= vec.vector;
			return *this;
		}

		template<glm::length_t L, class T>
		inline Vector<L, T>& Vector<L, T>::operator*=(const Vector<L, T>& vec)
		{
			vector *= vec.vector;
			return *this;
		}

		template<glm::length_t L, class T>
		inline Vector<L, T>& Vector<L, T>::operator/=(const Vector<L, T>& vec)
		{
			vector /= vec.vector;
			return *this;
		}

		template<glm::length_t L, class T>
		inline Vector<L, T>& Vector<L, T>::operator*=(const T& scalar)
		{
			vector *= scalar;
			return *this;
		}

		template<glm::length_t L, class T>
		inline T Vector<L, T>::Dot(const Vector<L, T>& lhs, const Vector<L, T>& rhs)
		{
			return (T)glm::dot(lhs.vector, rhs.vector);
		}

		template<glm::length_t L, class T>
		inline Vector<3, T> Vector<L, T>::Cross(const Vector<3, T>& lhs, const Vector<3, T>& rhs)
		{
			return Vector<3, T>(glm::cross(lhs.vector, rhs.vector));
		}

		template<glm::length_t L, class T>
		inline T Vector<L, T>::Distance(const Vector<3, T>& lhs, const Vector<3, T>& rhs)
		{
			return (T)glm::distance(lhs.vector, rhs.vector);
		}

		template<glm::length_t L, class T>
		inline T& Vector<L, T>::operator[](int index)
		{
			return vector[index];
		}

		template<glm::length_t L, class T>
		inline const T& Vector<L, T>::operator[](int index) const
		{
			return vector[index];
		}
		template<glm::length_t L, class T>
		inline Vector<L, T>::operator glm::vec<L, T, glm::packed_highp>() const
		{
			return vector;
		}
		template<glm::length_t L, class T>
		inline Vector<L, T> Vector<L, T>::Normalized() const
		{
			return Vector<L, T>{glm::normalize(vector)};
		}
		template<glm::length_t L, class T>
		inline float Vector<L, T>::Magnitude() const
		{
			return glm::length(vector);
		}
		template<glm::length_t L, class T>
		inline float Vector<L, T>::Magnitude2() const
		{
			return glm::length2(vector);
		}
		template<glm::length_t L, class T>
		inline T& Vector<L, T>::x()
		{
			return vector[0];
		}
		template<glm::length_t L, class T>
		inline T& Vector<L, T>::y()
		{
			return vector[1];
		}
		template<glm::length_t L, class T>
		inline T& Vector<L, T>::z()
		{
			return vector[2];
		}
		template<glm::length_t L, class T>
		inline T& Vector<L, T>::w()
		{
			return vector[3];
		}
		template<glm::length_t L, class T>
		inline const T& Vector<L, T>::x() const
		{
			return vector[0];
		}
		template<glm::length_t L, class T>
		inline const T& Vector<L, T>::y() const
		{
			return vector[1];
		}
		template<glm::length_t L, class T>
		inline const T& Vector<L, T>::z() const
		{
			return vector[2];
		}
		template<glm::length_t L, class T>
		inline const T& Vector<L, T>::w() const
		{
			return vector[3];
		}
	}

	using Vector1 = priv::Vector<1, float>;
	using Vector2 = priv::Vector<2, float>;
	using Vector3 = priv::Vector<3, float>;
	using Vector4 = priv::Vector<4, float>;
}
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

namespace won
{
	namespace priv
	{
		template<glm::length_t C, glm::length_t R, class T> 
		class Matrix
		{
		public:
			Matrix();

		private:
			glm::mat<C, R, T, glm::packed_highp> matrix;
		};
	}

	using Matrix2x2 = priv::Matrix<2, 2, glm::f32>;
	using Matrix3x3 = priv::Matrix<3, 3, glm::f32>;
	using Matrix4x4 = priv::Matrix<4, 4, glm::f32>;
}
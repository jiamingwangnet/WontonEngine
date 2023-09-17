#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

namespace won
{
	namespace priv
	{
		template<glm::length_t L, class T>
		class Vector
		{
		public:
			Vector();

		private:
			glm::vec<L, T, glm::packed_highp> vector;
		};
	}

	using Vector1 = priv::Vector<1, float>;
	using Vector2 = priv::Vector<2, float>;
	using Vector3 = priv::Vector<3, float>;
	using Vector4 = priv::Vector<4, float>;
}
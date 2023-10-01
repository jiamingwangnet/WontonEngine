#pragma once

#include "../Math/Vector.h"
#include "../Math/Matrix.h"
#include "Texture.h"
#include "../AssetManagerBase.h"
#include <string>
#include <cstdint>

namespace won
{
	namespace priv
	{
		class ShaderBase
		{
		public:
			ShaderBase(unsigned int programId);

			void SetInt(const std::string& name, int value) const;
			void SetFloat(const std::string& name, float value) const;
			void SetVec2(const std::string& name, Vector2 value) const;
			void SetVec3(const std::string& name, Vector3 value) const;
			void SetVec4(const std::string& name, Vector4 value) const;
			void SetMat2(const std::string& name, Matrix2x2 value) const;
			void SetMat3(const std::string& name, Matrix3x3 value) const;
			void SetMat4(const std::string& name, Matrix4x4 value) const;

			// Check if texture is bound
			// sets the uniform to the texture's unit number
			void SetTexture(const std::string& name, Texture value) const;

		private:
			void Activate() const;
			void Deactivate() const;

			uint32_t GetUniformLoc(const std::string& name) const;

		private:
			unsigned int progId;

			friend class MaterialBase;
			friend class ScreenRenderer;
		};
	}

	using Shader = priv::ShaderBase*;

	class ShaderManager
	{
	public:
		// input the source codes
		static Shader CreateShader(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader);
		static Shader GetShader(const std::string& name);

	private:
		static priv::AssetManagerBase<priv::ShaderBase, Shader> assetManager;
	};
}
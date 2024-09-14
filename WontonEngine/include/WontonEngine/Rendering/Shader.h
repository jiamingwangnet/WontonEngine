#pragma once

#include "../Math/Vector.h"
#include "../Math/Matrix.h"
#include "Texture.h"
#include "../IAssetManager.h"
#include "../Color.h"
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

			void SetInt(const char* name, int value) const;
			void SetFloat(const char* name, float value) const;
			void SetVec2(const char* name, Vector2 value) const;
			void SetVec3(const char* name, Vector3 value) const;
			void SetVec4(const char* name, Vector4 value) const;
			void SetMat2(const char* name, Matrix2x2 value) const;
			void SetMat3(const char* name, Matrix3x3 value) const;
			void SetMat4(const char* name, Matrix4x4 value) const;

			// does nothing if uniform is not found
			void SetIntNoThrow(const std::string& name, int value) const noexcept;
			void SetFloatNoThrow(const std::string& name, float value) const noexcept;
			void SetVec2NoThrow(const std::string& name, Vector2 value) const noexcept;
			void SetVec3NoThrow(const std::string& name, Vector3 value) const noexcept;
			void SetVec4NoThrow(const std::string& name, Vector4 value) const noexcept;
			void SetMat2NoThrow(const std::string& name, Matrix2x2 value) const noexcept;
			void SetMat3NoThrow(const std::string& name, Matrix3x3 value) const noexcept;
			void SetMat4NoThrow(const std::string& name, Matrix4x4 value) const noexcept;

			void SetIntNoThrow(const char* name, int value) const noexcept;
			void SetFloatNoThrow(const char* name, float value) const noexcept;
			void SetVec2NoThrow(const char* name, Vector2 value) const noexcept;
			void SetVec3NoThrow(const char* name, Vector3 value) const noexcept;
			void SetVec4NoThrow(const char* name, Vector4 value) const noexcept;
			void SetMat2NoThrow(const char* name, Matrix2x2 value) const noexcept;
			void SetMat3NoThrow(const char* name, Matrix3x3 value) const noexcept;
			void SetMat4NoThrow(const char* name, Matrix4x4 value) const noexcept;

			// Check if texture is bound
			// sets the uniform to the texture's unit number
			void SetTexture(const std::string& name, Texture value) const;
			void SetTexture(const const char* name, Texture value) const;
			void SetTextureNoThrow(const std::string& name, Texture value) const noexcept;
			void SetTextureNoThrow(const char* name, Texture value) const noexcept;

			// normalize color value and convert to vec4
			void SetColor(const std::string& name, Color color) const;
			void SetColor(const const char* name, Color color) const;
			void SetColorNoThrow(const std::string& name, Color color) const noexcept;
			void SetColorNoThrow(const char* name, Color color) const noexcept;

		private:
			void Activate() const;
			void Deactivate() const;

			uint32_t GetUniformLoc(const std::string& name) const;
			uint32_t GetUniformLoc(const char* name) const;
			uint32_t GetUniformLocNoThrow(const std::string& name) const noexcept;
			uint32_t GetUniformLocNoThrow(const char* name) const noexcept;

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
		static priv::IAssetManager<priv::ShaderBase, Shader> assetManager;
	};
}
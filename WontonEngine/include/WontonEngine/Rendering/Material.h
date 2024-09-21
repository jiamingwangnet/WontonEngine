#pragma once

#include "Shader.h"
#include "../IAssetManager.h"
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

namespace won
{
	enum class UniformType
	{
		Int,
		Float,
		Vec2,
		Vec3,
		Vec4, 
		Mat2,
		Mat3,
		Mat4,
		Texture,
		Color
	};

	namespace priv
	{
		struct IUniformData;
	}

	using UniformDataList = std::vector<std::unique_ptr<priv::IUniformData>>;

	namespace priv
	{
		struct IUniformData
		{
			UniformType type;
			std::string name;
		};

		class MaterialBase
		{
		public:
			MaterialBase(Shader shader, UniformDataList&& data);

			Shader GetShader() const;
			const UniformDataList& GetSettings() const;

			void Activate() const;
			void Deactivate() const;
		private:
			Shader shader;
			UniformDataList info;
			bool uniformsSet = false;
		};
	}

	using Material = priv::MaterialBase*;

	template<class T>
	struct UniformData : public priv::IUniformData
	{
		UniformData(UniformType type, const std::string& name, T value);

		T value;

		// static function to generate a UniformData class
		static std::unique_ptr<priv::IUniformData> GenData(const std::string& name, UniformType type, T value);
	};

	class MaterialManager
	{
	public:
		static Material CreateMaterial(const std::string& name, Shader shader, UniformDataList&& data);
		static Material GetMaterial(const std::string& name);

	private:
		static priv::IAssetManager<priv::MaterialBase, Material> assetManager;
	};

	template<class T>
	inline UniformData<T>::UniformData(UniformType type, const std::string& name, T value)
		: priv::IUniformData{type, name}, value{value}
	{}

	template<class T>
	inline std::unique_ptr<priv::IUniformData> UniformData<T>::GenData(const std::string& name, UniformType type, T value)
	{
		std::unique_ptr<priv::IUniformData> data = std::make_unique<UniformData<T>>(type, name, value);
		
		return data;
	}
}
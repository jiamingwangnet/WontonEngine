#pragma once

#include "Shader.h"
#include "../AssetManagerBase.h"
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
		Texture
	};

	namespace priv
	{
		struct UniformDataBase;
	}

	using UniformDataList = std::vector<std::unique_ptr<priv::UniformDataBase>>;

	namespace priv
	{
		struct UniformDataBase
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
		private:
			Shader shader;
			UniformDataList info;
		};
	}

	using Material = priv::MaterialBase*;

	template<class T>
	struct UniformData : public priv::UniformDataBase
	{
		T value;

		// static function to generate a UniformData class
		static std::unique_ptr<priv::UniformDataBase> GenData(const std::string& name, UniformType type, T value);
	};

	class MaterialManager
	{
	public:
		static Material CreateMaterial(const std::string& name, Shader shader, UniformDataList&& data);
		static Material GetMaterial(const std::string& name);

	private:
		static priv::AssetManagerBase<priv::MaterialBase, Material> assetManager;
	};
}
#include "include/WontonEngine/Rendering/Material.h"
#include "include/WontonEngine/Math/Matrix.h"
#include "include/WontonEngine/Math/Vector.h"

won::priv::AssetManagerBase<won::priv::MaterialBase, won::Material> won::MaterialManager::assetManager;

won::priv::MaterialBase::MaterialBase(Shader shader, UniformDataList&& data)
	: shader{shader}, info{std::move(data)}
{}

won::Shader won::priv::MaterialBase::GetShader() const
{
	return shader;
}

const won::UniformDataList& won::priv::MaterialBase::GetSettings() const
{
	return info;
}

void won::priv::MaterialBase::Activate() const
{
	shader->Activate();

	for (const std::unique_ptr<priv::UniformDataBase>& data : info)
	{
		switch (data->type)
		{
		case UniformType::Int:
		{
			UniformData<int>* finalData = static_cast<UniformData<int>*>(data.get());
			shader->SetInt(finalData->name, finalData->value);
			break;
		}
		case UniformType::Float:
		{
			UniformData<float>* finalData = static_cast<UniformData<float>*>(data.get());
			shader->SetFloat(finalData->name, finalData->value);
			break;
		}
		case UniformType::Mat2:
		{
			UniformData<Matrix2x2>* finalData = static_cast<UniformData<Matrix2x2>*>(data.get());
			shader->SetMat2(finalData->name, finalData->value);
			break;
		}
		case UniformType::Mat3:
		{
			UniformData<Matrix3x3>* finalData = static_cast<UniformData<Matrix3x3>*>(data.get());
			shader->SetMat3(finalData->name, finalData->value);
			break;
		}
		case UniformType::Mat4:
		{
			UniformData<Matrix4x4>* finalData = static_cast<UniformData<Matrix4x4>*>(data.get());
			shader->SetMat4(finalData->name, finalData->value);
			break;
		}
		case UniformType::Vec2:
		{
			UniformData<Vector2>* finalData = static_cast<UniformData<Vector2>*>(data.get());
			shader->SetVec2(finalData->name, finalData->value);
			break;
		}
		case UniformType::Vec3:
		{
			UniformData<Vector3>* finalData = static_cast<UniformData<Vector3>*>(data.get());
			shader->SetVec3(finalData->name, finalData->value);
			break;
		}
		case UniformType::Vec4:
		{
			UniformData<Vector4>* finalData = static_cast<UniformData<Vector4>*>(data.get());
			shader->SetVec4(finalData->name, finalData->value);
			break;
		}
		case UniformType::Texture:
		{
			UniformData<Texture>* finalData = static_cast<UniformData<Texture>*>(data.get());
			finalData->value->BindTexture();
			shader->SetTexture(finalData->name, finalData->value);
			break;
		}
		}
	}
}

void won::priv::MaterialBase::Deactivate() const
{
	shader->Deactivate();

	// unbind textures
	for (const std::unique_ptr<priv::UniformDataBase>& data : info)
	{
		if (data->type == UniformType::Texture)
		{
			UniformData<Texture>* finalData = static_cast<UniformData<Texture>*>(data.get());
			finalData->value->UnbindTexture();
		}
	}
}

won::Material won::MaterialManager::CreateMaterial(const std::string& name, Shader shader, UniformDataList&& data)
{
	return assetManager.CreateAsset(name, shader, std::move(data));
}

won::Material won::MaterialManager::GetMaterial(const std::string& name)
{
	return assetManager.GetAsset(name);
}

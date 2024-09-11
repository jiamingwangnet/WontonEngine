#include "include/WontonEngine/Rendering/Texture.h"
#include <glad/glad.h>
#include <stb/stb_image.h>
#include <cassert>
#include <thread>
#include "include/WontonEngine/Game.h"

unsigned int won::priv::TextureBase::unitCounter = 0;
won::priv::IAssetManager<won::priv::TextureBase, won::Texture> won::TextureManager::assetManager;

won::priv::TextureBase::TextureBase(unsigned int id)
	: id{id}
{}

unsigned int won::priv::TextureBase::GetId() const
{
	return id;
}

unsigned int won::priv::TextureBase::GetUnit() const
{
	return unit;
}

void won::priv::TextureBase::BindTexture()
{
	unit = unitCounter++;
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, id);
}

void won::priv::TextureBase::UnbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	unitCounter--;
	unit = (unsigned int)-1;
}

won::Texture won::TextureManager::CreateTexture(const std::string& name, const std::string& path, bool mipmap, TextureWrap wrapMethod, TextureFilter magFilter, TextureFilter minFilter)
{
	// load image from file
	stbi_set_flip_vertically_on_load(true);

	int width, height, bbp;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &bbp, 0);

	Texture tex = CreateTexture(name, data, width, height, mipmap, wrapMethod, magFilter, minFilter);

	stbi_image_free(data);

	return tex;
}

won::Texture won::TextureManager::CreateTexture(const std::string& name, unsigned char* data, int width, int height, bool mipmap, TextureWrap wrapMethod, TextureFilter magFilter, TextureFilter minFilter)
{
	// generate texture
	unsigned int texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	switch (wrapMethod)
	{
	case TextureWrap::Repeat:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		break;
	case TextureWrap::MirroredRepeat:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		break;
	case TextureWrap::ClampToEdge:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		break;
	}

	switch ((int)magFilter)
	{
	case (int)TextureFilter::Nearest:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	case (int)TextureFilter::Linear:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case (int)TextureFilter::MipmapNearest:
	case (int)TextureFilter::Nearest | (int)TextureFilter::MipmapNearest:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		break;
	case (int)TextureFilter::MipmapLinear:
	case (int)TextureFilter::Linear | (int)TextureFilter::MipmapLinear:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		break;
	case (int)TextureFilter::Linear | (int)TextureFilter::MipmapNearest:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		break;
	case (int)TextureFilter::Nearest | (int)TextureFilter::MipmapLinear:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		break;
	}

	switch ((int)minFilter)
	{
	case (int)TextureFilter::Nearest:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		break;
	case (int)TextureFilter::Linear:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		break;
	case (int)TextureFilter::MipmapNearest:
	case (int)TextureFilter::Nearest | (int)TextureFilter::MipmapNearest:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		break;
	case (int)TextureFilter::MipmapLinear:
	case (int)TextureFilter::Linear | (int)TextureFilter::MipmapLinear:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		break;
	case (int)TextureFilter::Linear | (int)TextureFilter::MipmapNearest:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		break;
	case (int)TextureFilter::Nearest | (int)TextureFilter::MipmapLinear:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		break;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	if (mipmap) glGenerateMipmap(GL_TEXTURE_2D);

	assetManager.CreateAsset(name, texture);

	return assetManager.GetAsset(name);
}

won::Texture won::TextureManager::GetTexture(const std::string& name)
{
	return assetManager.GetAsset(name);
}

#include "include/WontonEngine/Rendering/Shader.h"
#include "include/WontonEngine/Error.h"
#include <glad/glad.h>
#include <thread>
#include "include/WontonEngine/Game.h"

// TODO: change to a file stream
#include <iostream>

won::priv::AssetManagerBase<won::priv::ShaderBase, won::Shader> won::ShaderManager::assetManager;

won::priv::ShaderBase::ShaderBase(unsigned int programId)
	: progId{programId}
{}

void won::priv::ShaderBase::SetInt(const std::string & name, int value) const
{
	glUniform1i(GetUniformLoc(name), value);
}

void won::priv::ShaderBase::SetFloat(const std::string& name, float value) const
{
	glUniform1f(GetUniformLoc(name), value);
}

void won::priv::ShaderBase::SetVec2(const std::string& name, Vector2 value) const
{
	glUniform2f(GetUniformLoc(name), value[0], value[1]);
}

void won::priv::ShaderBase::SetVec3(const std::string& name, Vector3 value) const
{
	glUniform3f(GetUniformLoc(name), value[0], value[1], value[2]);
}

void won::priv::ShaderBase::SetVec4(const std::string& name, Vector4 value) const
{
	glUniform4f(GetUniformLoc(name), value[0], value[1], value[2], value[3]);
}

void won::priv::ShaderBase::SetMat2(const std::string& name, Matrix2x2 value) const
{
	glUniformMatrix2fv(GetUniformLoc(name), 1, GL_FALSE, &value[0][0]);
}

void won::priv::ShaderBase::SetMat3(const std::string& name, Matrix3x3 value) const
{
	glUniformMatrix3fv(GetUniformLoc(name), 1, GL_FALSE, &value[0][0]);
}

void won::priv::ShaderBase::SetMat4(const std::string& name, Matrix4x4 value) const
{
	glUniformMatrix4fv(GetUniformLoc(name), 1, GL_FALSE, &value[0][0]);
}

void won::priv::ShaderBase::SetTexture(const std::string& name, Texture value) const
{
	if (value->GetUnit() == (unsigned int)-1)
		Error::ThrowError("Texture is not bound.", std::cout, __LINE__, __FILE__);

	glUniform1i(GetUniformLoc(name), value->GetUnit());
}

void won::priv::ShaderBase::SetColor(const std::string& name, Color color) const
{
	SetVec4(name, won::Vector4{ (float)color.r / 255.0f, (float)color.g / 255.0f, (float)color.b / 255.0f, (float)color.a / 255.0f });
}

void won::priv::ShaderBase::Activate() const
{
	glUseProgram(progId);
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);
}

void won::priv::ShaderBase::Deactivate() const
{
	glUseProgram(0);
	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
	//glDisableVertexAttribArray(2);
}

uint32_t won::priv::ShaderBase::GetUniformLoc(const std::string& name) const
{
	GLint loc = glGetUniformLocation(progId, name.c_str());
	if (loc == GL_INVALID_INDEX)
		Error::ThrowError((std::string)"Uniform" + name + " not found in shader.", std::cout, __LINE__, __FILE__);
	return (uint32_t)loc;
}

won::Shader won::ShaderManager::CreateShader(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader)
{
	const char* vertSource = vertexShader.c_str();
	const char* fragSource = fragmentShader.c_str();

	unsigned int vertex, fragment;

	int success;
	char infoLog[512] = {0};

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertSource, nullptr);
	glCompileShader(vertex);

	// log errors
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		Error::ThrowError((std::string)"Vertex shader failed to compile: \n" + infoLog, std::cout, __LINE__, __FILE__);
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragSource, nullptr);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
		Error::ThrowError((std::string)"Fragment shader failed to compile: \n" + infoLog, std::cout, __LINE__, __FILE__);
	}

	unsigned int id;

	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);

	glGetShaderiv(fragment, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
		Error::ThrowError((std::string)"Shader failed to link: \n" + infoLog, std::cout, __LINE__, __FILE__);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	assetManager.CreateAsset(name, id);

	return assetManager.GetAsset(name);
}

won::Shader won::ShaderManager::GetShader(const std::string& name)
{
	return assetManager.GetAsset(name);
}

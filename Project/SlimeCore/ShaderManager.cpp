#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
	printf("Deleteing ShaderManager:\n");

	for (int i = 0; i < shaderList.size(); i++)
	{
		if (shaderList[i] != nullptr)
		{
			printf(" - Deleteing shader: %s.\n", shaderList[i]->name.c_str());
			delete shaderList[i];
			shaderList[i] = nullptr;
		}
	}
	printf("\n");
}

Shader* ShaderManager::GetShaderByName(bool creation, const char* name)
{
	for (int i = 0; i < shaderList.size(); i++)
	{
		if (shaderList[i]->name == name)
		{
			return shaderList[i];
		}
	}

	return ShaderNotFound(creation, name);
}

Shader* ShaderManager::GetShaderByIndex(int index)
{
	return shaderList[index] ? shaderList[index] : ShaderNotFound(false);
}

bool ShaderManager::CreateShader(const char* name, const char* vertex, const char* fragment)
{
	if (GetShaderByName(true,name) == nullptr)
	{
		printf("Creating Shader with name: %s.\n", name);
		AddShader(new Shader(name, vertex, fragment));
		return true;
	}
	printf("Shader already exist with name: %s.\n", name);
	return false;
}

Shader* ShaderManager::ShaderNotFound(bool creation, const char* name, int index)
{
	if (!creation)
		printf("Shader Not Found with name: %s, index: %d.\n", name, index);
	
	return nullptr;
}

bool ShaderManager::AddShader(Shader* newShader)
{
	shaderList.push_back(newShader);
	return true;
}

bool ShaderManager::DebugManager()
{
	printf("Shaders: \n");
	for (int i = 0; i < shaderList.size(); i++)
	{
		std::cout << " - " << shaderList[i]->name << std::endl;
	}
	printf("\n");
	return true;
}
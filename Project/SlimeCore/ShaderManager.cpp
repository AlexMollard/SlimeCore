#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
	for (int i = 0; i < shaderList.size(); i++)
	{
		if (shaderList[i] != nullptr)
		{
			delete shaderList[i];
			shaderList[i] = nullptr;
		}
	}
}

Shader* ShaderManager::Get(const char* name, bool creation)
{
	for (int i = 0; i < shaderList.size(); i++)
	{
		if (shaderList[i]->name == name)
		{
			return shaderList[i];
		}
	}

	return NotFound(creation, name);
}

Shader* ShaderManager::Get(int index)
{
	return shaderList[index] ? shaderList[index] : NotFound(false);
}

bool ShaderManager::Create(const char* name, const char* vertex, const char* fragment)
{
	if (Get(name,true) == nullptr)
	{
		Add(new Shader(name, vertex, fragment));
		return true;
	}
	printf("Shader already exist with name: %s.\n", name);
	return false;
}

Shader* ShaderManager::NotFound(bool creation, const char* name, int index)
{
	if (!creation)
		printf("Shader Not Found with name: %s, index: %d.\n", name, index);
	
	return nullptr;
}

bool ShaderManager::Add(Shader* newShader)
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
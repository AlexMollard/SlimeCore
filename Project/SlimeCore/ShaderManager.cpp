#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
	Create("None");

	// Shaders
	Create("skyBoxShader", "..\\Shaders\\SkyBoxVertex.shader", "..\\Shaders\\SkyBoxFragment.shader");
	Create("defaultShader", "..\\Shaders\\Vertex.shader", "..\\Shaders\\Fragment.shader");
	Create("pbrShader", "..\\Shaders\\PbrVertex.shader", "..\\Shaders\\PbrFragment.shader");
	Create("lightShader", "..\\Shaders\\litVertex.shader", "..\\Shaders\\litFragment.shader");
	Create("2DShader", "..\\Shaders\\DebugVertex.shader", "..\\Shaders\\DebugFragment.shader");
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

Shader* ShaderManager::Get(std::string name, bool creation)
{
	for (int i = 0; i < shaderList.size(); i++)
	{
		if (shaderList[i]->GetName() == name)
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

Shader* ShaderManager::Create(std::string name, const char* vertex, const char* fragment, const char* geometry)
{
	if (Get(name, true) == nullptr)
	{
		Shader* tempShader = new Shader(name, vertex, fragment, geometry);
		Add(tempShader);
		return tempShader;
	}
	printf("Shader already exist with name: %s.\n", name);
	return nullptr;
}

bool ShaderManager::Create(std::string name)
{
	if (Get(name, true) == nullptr)
	{
		Add(new Shader(name));
		return true;
	}
	printf("Shader already exist with name: %s.\n", name);
	return false;
}

int ShaderManager::GetIndex(Shader* shader)
{
	for (int i = 0; i < shaderList.size(); i++)
	{
		if (shaderList[i] == shader)
		{
			return i;
		}
	}
	std::cout << "Cannot find Shader: " << shader->GetName() << ".\n";
	return -404;
}

void ShaderManager::SetNames()
{
	names.clear();
	for (int i = 0; i < shaderList.size(); i++)
	{
		names.push_back(shaderList[i]->GetName());
	}
}

std::vector<std::string> ShaderManager::GetNames()
{
	SetNames();
	return names;
}

Shader* ShaderManager::NotFound(bool creation, std::string name, int index)
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
		std::cout << " - " << shaderList[i]->GetName() << std::endl;
	}
	printf("\n");
	return true;
}
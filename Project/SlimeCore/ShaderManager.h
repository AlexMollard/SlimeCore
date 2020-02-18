#pragma once
#include "Shader.h"

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	Shader* GetShaderByName(bool creation, const char* name);
	Shader* GetShaderByIndex(int index);

	Shader* ShaderNotFound(bool creation, const char* name = "---", int index = 404);
	bool AddShader(Shader* newShader);
	bool CreateShader(const char* name, const char* vertex, const char* fragment);

	bool DebugManager();

protected:
	std::vector<Shader*> shaderList;
};


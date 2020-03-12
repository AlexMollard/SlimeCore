#pragma once
#include "Shader.h"

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	Shader* Get(std::string name, bool creation = false);
	Shader* Get(int index);

	Shader* NotFound(bool creation, std::string name = "---", int index = -404);
	bool Add(Shader* newShader);
	bool Create(std::string name, const char* vertex, const char* fragment);
	bool Create(std::string name);

	int GetIndex(Shader* shader);

	void SetNames();
	std::vector<std::string> GetNames();

	bool DebugManager();

protected:
	std::vector<std::string> names;
	std::vector<Shader*> shaderList;
};


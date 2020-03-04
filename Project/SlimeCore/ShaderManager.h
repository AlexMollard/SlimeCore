#pragma once
#include "Shader.h"

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	Shader* Get(const char* name, bool creation = false);
	Shader* Get(int index);

	Shader* NotFound(bool creation, const char* name = "---", int index = 404);
	bool Add(Shader* newShader);
	bool Create(const char* name, const char* vertex, const char* fragment);
	bool Create(const char* name);

	void SetNames();
	std::vector<std::string> GetNames();

	bool DebugManager();

protected:
	std::vector<std::string> names;
	std::vector<Shader*> shaderList;
};


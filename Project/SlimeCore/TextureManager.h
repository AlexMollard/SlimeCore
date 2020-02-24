#pragma once
#include "Texture.h"
#include <vector>
class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	Texture* Get(const char* name, bool creation = false);
	Texture* Get(int index);

	Texture* NotFound(bool creation, const char* name = "---", int index = 404);
	bool Add(Texture* newTexture);
	bool Create(const char* name, std::string dir);

	unsigned int CreateSkyBox(std::vector<std::string> faces);
	unsigned int GetSkyBox();

	bool DebugManager();
protected:
	std::vector<Texture*> textureList;
	Texture* skyBox;
	unsigned int skyboxID = 0;
};


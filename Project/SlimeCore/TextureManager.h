#pragma once
#include "Texture.h"
#include <vector>

class TextureManager
{
public:

	TextureManager();
	~TextureManager();

	Texture* Get(const char* name, TEXTURETYPE type, bool creation = false);
	Texture* Get(int index, TEXTURETYPE type);

	Texture* NotFound(bool creation, const char* name = "---", int index = 404);

	std::vector<Texture*> GetTextureList(TEXTURETYPE type);

	bool Add(Texture* newTexture, TEXTURETYPE type);
	bool Create(const char* name, std::string dir, TEXTURETYPE type);

	void SetNameList();
	std::vector<std::string> GetNameList(TEXTURETYPE type);
	int GetTextureIndex(std::string name, TEXTURETYPE type);

	unsigned int CreateSkyBox(std::vector<std::string> faces);
	Texture* GetSkyBox();

	bool DebugManager();
protected:
	std::vector<Texture*> diffuseList;
	std::vector<std::string> diffuseNames;

	std::vector<Texture*> specularList;
	std::vector<std::string> specularNames;

	std::vector<Texture*> normalList;
	std::vector<std::string> normalNames;

	std::vector<Texture*> specularColorList;
	std::vector<std::string> specularColorNames;

	Texture* skyBox;
	unsigned int skyboxID = 0;
};


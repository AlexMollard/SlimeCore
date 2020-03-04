#pragma once
#include "Texture.h"
#include <vector>

class TextureManager
{
public:

	TextureManager();
	~TextureManager();

	Texture* Get(std::string, TEXTURETYPE type, bool creation = false);
	Texture* Get(int index, TEXTURETYPE type);

	Texture* NotFound(bool creation, std::string name = "---", int index = 404);

	std::vector<Texture*> GetTextureList(TEXTURETYPE type);

	void ImportAllTextures();
	std::vector<std::string> GetAllFiles(std::string dir);

	bool Add(Texture* newTexture, TEXTURETYPE type);
	bool Create(std::string, std::string dir, TEXTURETYPE type);
	void Create(std::vector<std::string> dirs, TEXTURETYPE type);
	void Create(std::string name);

	void SetNameList();
	std::vector<std::string> GetNameList(TEXTURETYPE type);
	int GetTextureIndex(std::string name, TEXTURETYPE type);

	unsigned int CreateSkyBox(std::string facesDIR);
	Texture* GetSkyBox();

	bool DebugManager();
protected:
	std::vector<Texture*> diffuseList;
	std::vector<std::string> diffuseNames;

	std::vector<Texture*> specularList;
	std::vector<std::string> specularNames;

	std::vector<Texture*> normalList;
	std::vector<std::string> normalNames;

	std::vector<Texture*> ambientList;
	std::vector<std::string> ambientNames;

	std::vector<Texture*> roughList;
	std::vector<std::string> roughNames;

	Texture* skyBox;
	unsigned int skyboxID = 0;
};


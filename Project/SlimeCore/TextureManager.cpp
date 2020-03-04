#include "TextureManager.h"
#include "gl_core_4_5.h"
#include "stb_image.h"
#include "dirent.h"
#include <iostream>
TextureManager::TextureManager()
{
	CreateBlanks("../Images/None.png");
}

TextureManager::~TextureManager()
{
	Texture* none = Get("None", TEXTURETYPE::Diffuse);
	delete none;
	none = nullptr;

	for (int i = 1; i < diffuseList.size(); i++)
	{
		if (diffuseList[i])
		{
			delete diffuseList[i];
			diffuseList[i] = nullptr;
		}
	}

	for (int i = 1; i < specularList.size(); i++)
	{
		if (specularList[i] != nullptr)
		{
			delete specularList[i];
			specularList[i] = nullptr;
		}
	}

	for (int i = 1; i < normalList.size(); i++)
	{
		if (normalList[i] != nullptr)
		{
			delete normalList[i];
			normalList[i] = nullptr;
		}
	}

	for (int i = 1; i < ambientList.size(); i++)
	{
		if (ambientList[i] != nullptr)
		{
			delete ambientList[i];
			ambientList[i] = nullptr;
		}
	}

	for (int i = 1; i < roughList.size(); i++)
	{
		if (roughList[i] != nullptr	)
		{
			delete roughList[i];
			roughList[i] = nullptr;
		}
	}


	delete skyBox;
}

Texture* TextureManager::Get(std::string name, TEXTURETYPE type, bool creation)
{
	std::vector<std::string> textureNameList = GetNameList(type);
	std::vector<Texture*> textureList = GetTextureList(type);

	for (int i = 0; i < textureNameList.size(); i++)
	{
		if (textureNameList[i] == std::string(name))
		{
			return textureList[i];
		}
	}

	return NotFound(creation, name);
}

Texture* TextureManager::Get(int index, TEXTURETYPE type)
{
	std::vector<Texture*> textureList = GetTextureList(type);


	return textureList[index] ? textureList[index] : NotFound(false, "---", index);
}

bool TextureManager::Create(std::string name, std::string dir, TEXTURETYPE type)
{
	if (Get(name,type, true) == nullptr)
	{
		Add(new Texture(name, dir), type);
		return true;
	}

	printf("Texture already exist with name: %s.\n", name.c_str());
	return false;
}

void TextureManager::Create(std::vector<std::string> dirs, TEXTURETYPE type)
{
	for (int i = 0; i < dirs.size(); i += 2)
	{
		Create(dirs[i], dirs[i + 1], type);
	}
}

void TextureManager::CreateBlanks(std::string dir)
{
	Texture* tex = new Texture("None",dir);
	diffuseList.push_back(tex);
	specularList.push_back(tex);
	normalList.push_back(tex);
	ambientList.push_back(tex);
	roughList.push_back(tex);
}

void TextureManager::SetNameList()
{
	if (diffuseList.size() > 0)
	{
		diffuseNames.clear();
		for (int i = 0; i < diffuseList.size(); i++)
		{
			diffuseNames.push_back(diffuseList[i]->name);
		}
	}
	
	if (specularList.size() > 0)
	{
		specularNames.clear();
		for (int i = 0; i < specularList.size(); i++)
		{
			specularNames.push_back(specularList[i]->name);
		}
	}
	
	if (normalList.size() > 0)
	{
		normalNames.clear();
		for (int i = 0; i < normalList.size(); i++)
		{
			normalNames.push_back(normalList[i]->name);
		}
	}

	if (ambientList.size() > 0)
	{
		ambientNames.clear();
		for (int i = 0; i < ambientList.size(); i++)
		{
			ambientNames.push_back(ambientList[i]->name);
		}
	}

	if (roughList.size() > 0)
	{
		roughNames.clear();
		for (int i = 0; i < roughList.size(); i++)
		{
			roughNames.push_back(roughList[i]->name);
		}
	}
}

std::vector<std::string> TextureManager::GetNameList(TEXTURETYPE type)
{
	SetNameList();
	switch (type)
	{
	case TEXTURETYPE::Diffuse:
		return diffuseNames;
		break;
	case TEXTURETYPE::Specular:
		return specularNames;
		break;
	case TEXTURETYPE::Normal:
		return normalNames;
		break;
	case TEXTURETYPE::Ambient:
		return ambientNames;
		break;
	case TEXTURETYPE::SkyBox:
		printf("There is no skybox vector");
		break;
	case TEXTURETYPE::Rough:
		return roughNames;
		break;
	default:
		break;
	}
}

int TextureManager::GetTextureIndex(std::string name, TEXTURETYPE type)
{
	std::vector<Texture*> textureList = GetTextureList(type);

	for (int i = 0; i < textureList.size(); i++)
	{
		if (textureList[i]->name == name)
			return i;
	}
	return 0;
}

unsigned int TextureManager::CreateSkyBox(std::string facesDIR)
{
	std::vector<std::string> dirs = GetAllFiles(facesDIR);
	std::vector<std::string> faces;

	for (int i = 0; i < dirs.size(); i+=2)
	{
		faces.push_back(dirs[i + 1]);
	}

		glGenTextures(1, &skyboxID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxID);

		int width, height, nrChannels;
		for (unsigned int i = 0; i < faces.size(); i++)
		{
			unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
			//std::cout << faces[i] << ": " << nrChannels << std::endl;
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, nrChannels != 4 ? GL_RGB : GL_RGBA, width, height, 0, nrChannels != 4 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data
				);
				stbi_image_free(data);
			}
			else
			{
				std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
				stbi_image_free(data);
			}
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	
	Add(new Texture("Sky Box", &skyboxID), TEXTURETYPE::SkyBox);
	return 0;
}

Texture* TextureManager::GetSkyBox()
{
	return skyBox;
}

Texture* TextureManager::NotFound(bool creation, std::string name, int index)
{
	if (!creation)
		printf("Texture Not Found with name: %s, index: %d.\n", name.c_str(), index);

	return nullptr;
}

std::vector<Texture*> TextureManager::GetTextureList(TEXTURETYPE type)
{
	switch (type)
	{
	case TEXTURETYPE::Diffuse:
		return diffuseList;
		break;
	case TEXTURETYPE::Specular:
		return specularList;
		break;
	case TEXTURETYPE::Normal:
		return normalList;
		break;
	case TEXTURETYPE::Ambient:
		return ambientList;
		break;
	case TEXTURETYPE::SkyBox:
		printf("There is no skybox vector");
		break;
	case TEXTURETYPE::Rough:
		return roughList;
		break;
	default:
		break;
	}
}

void TextureManager::ImportAllTextures()
{
	Create(GetAllFiles("..\\Images\\Diffuse\\"), TEXTURETYPE::Diffuse);
	Create(GetAllFiles("..\\Images\\Specular\\"), TEXTURETYPE::Specular);
	Create(GetAllFiles("..\\Images\\Normal\\"), TEXTURETYPE::Normal);
	Create(GetAllFiles("..\\Images\\Ambient\\"), TEXTURETYPE::Ambient);
	Create(GetAllFiles("..\\Images\\Rough\\"), TEXTURETYPE::Rough);
}

std::vector<std::string> TextureManager::GetAllFiles(std::string dirType)
{
	std::vector<std::string> fileNames;
	DIR* dir;
	struct dirent* ent;
	if ((dir = opendir(dirType.c_str())) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			if (ent->d_name[0] != 46)
			{
				fileNames.push_back(ent->d_name);
				fileNames.push_back(std::string(dirType.c_str()) + ent->d_name);
			}
		}
		closedir(dir);
	}
	else {
		perror("");
	}

	return fileNames;
}

bool TextureManager::Add(Texture* newTexture, TEXTURETYPE type)
{
	switch (type)
	{
	case TEXTURETYPE::Diffuse:
		diffuseList.push_back(newTexture);
		break;
	case TEXTURETYPE::Specular:
		specularList.push_back(newTexture);
		break;
	case TEXTURETYPE::Normal:
		normalList.push_back(newTexture);
		break;
	case TEXTURETYPE::Ambient:
		ambientList.push_back(newTexture);
		break;
	case TEXTURETYPE::SkyBox:
		skyBox = newTexture;
		break;
	case TEXTURETYPE::Rough:
		roughList.push_back(newTexture);
		break;
	default:
		break;
	}

	return true;
}

bool TextureManager::DebugManager()
{
	printf("Textures: \n");
	printf(" Diffuse: \n");
	for (int i = 0; i < diffuseList.size(); i++)
	{
		std::cout << "  - " << diffuseList[i]->name << std::endl;
	}
	printf("\n");
	
	printf(" Specular: \n");
	for (int i = 0; i < specularList.size(); i++)
	{
		std::cout << "  - " << specularList[i]->name << std::endl;
	}
	printf("\n");

	printf(" Normal: \n");
	for (int i = 0; i < normalList.size(); i++)
	{
		std::cout << "  - " << normalList[i]->name << std::endl;
	}
	printf("\n");

	printf(" Ambient: \n");
	for (int i = 0; i < ambientList.size(); i++)
	{
		std::cout << "  - " << ambientList[i]->name << std::endl;
	}
	printf("\n");

	printf(" Rough: \n");
	for (int i = 0; i < ambientList.size(); i++)
	{
		std::cout << "  - " << roughList[i]->name << std::endl;
	}
	printf("\n");
	return true;
}
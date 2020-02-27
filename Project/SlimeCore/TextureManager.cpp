#include "TextureManager.h"
#include "gl_core_4_5.h"
#include "stb_image.h"


TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
	printf("Deleteing TextureManager:\n");

	for (int i = 0; i < diffuseList.size(); i++)
	{
		if (diffuseList[i] != nullptr)
		{
			printf(" - Deleteing Diffuse Texture: %s.\n", diffuseList[i]->name);
			delete diffuseList[i];
			diffuseList[i] = nullptr;
		}
	}

	for (int i = 0; i < specularList.size(); i++)
	{
		if (specularList[i] != nullptr)
		{
			printf(" - Deleteing Specular Texture: %s.\n", specularList[i]->name);
			delete specularList[i];
			specularList[i] = nullptr;
		}
	}

	for (int i = 0; i < normalList.size(); i++)
	{
		if (normalList[i] != nullptr)
		{
			printf(" - Deleteing Normal Texture: %s.\n", normalList[i]->name);
			delete normalList[i];
			normalList[i] = nullptr;
		}
	}

	for (int i = 0; i < ambientList.size(); i++)
	{
		if (ambientList[i] != nullptr)
		{
			printf(" - Deleteing Ambient Texture: %s.\n", ambientList[i]->name);
			delete ambientList[i];
			ambientList[i] = nullptr;
		}
	}

	printf(" - Deleteing Texture: SkyBox");
	delete skyBox;
	printf("\n");
}

Texture* TextureManager::Get(const char* name, TEXTURETYPE type, bool creation)
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

bool TextureManager::Create(const char* name, std::string dir, TEXTURETYPE type)
{
	if (Get(name,type, true) == nullptr)
	{
		printf("Creating Texture with name: %s.\n", name);
		Add(new Texture(name, dir), type);
		return true;
	}

	printf("Texture already exist with name: %s.\n", name);
	return false;
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

unsigned int TextureManager::CreateSkyBox(std::vector<std::string> faces)
{
		glGenTextures(1, &skyboxID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxID);

		int width, height, nrChannels;
		for (unsigned int i = 0; i < faces.size(); i++)
		{
			unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
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

Texture* TextureManager::NotFound(bool creation, const char* name, int index)
{
	if (!creation)
		printf("Texture Not Found with name: %s, index: %d.\n", name, index);

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
	default:
		break;
	}
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
	return true;
}
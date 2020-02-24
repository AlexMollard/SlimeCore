#include "TextureManager.h"
#include "gl_core_4_5.h"
#include "stb_image.h"

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
	printf("Deleteing TextureManager:\n");

	for (int i = 0; i < textureList.size(); i++)
	{
		if (textureList[i] != nullptr)
		{
			printf(" - Deleteing Texture: %s.\n", textureList[i]->name);
			delete textureList[i];
			textureList[i] = nullptr;
		}
	}
	printf("\n");
}

Texture* TextureManager::Get(const char* name, bool creation)
{
	for (int i = 0; i < textureList.size(); i++)
	{
		if (textureList[i]->name == name)
		{
			return textureList[i];
		}
	}

	return NotFound(creation, name);
}

Texture* TextureManager::Get(int index)
{
	return textureList[index] ? textureList[index] : NotFound(false, "---", index);
}

bool TextureManager::Create(const char* name, std::string dir)
{
	if (Get(name, true) == nullptr)
	{
		printf("Creating Texture with name: %s.\n", name);
		Add(new Texture(name, dir));
		return true;
	}

	printf("Texture already exist with name: %s.\n", name);
	return false;
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
	
	skyBox = new Texture("Sky Box", skyboxID);
	Add(skyBox);
	return skyboxID;
}

unsigned int TextureManager::GetSkyBox()
{
	return skyboxID;
}

Texture* TextureManager::NotFound(bool creation, const char* name, int index)
{
	if (!creation)
		printf("Texture Not Found with name: %s, index: %d.\n", name, index);

	return nullptr;
}

bool TextureManager::Add(Texture* newTexture)
{
	textureList.push_back(newTexture);
	return true;
}

bool TextureManager::DebugManager()
{
	printf("Textures: \n");
	for (int i = 0; i < textureList.size(); i++)
	{
		std::cout << " - " << textureList[i]->name << std::endl;
	}
	printf("\n");

	return true;
}
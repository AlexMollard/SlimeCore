#include "Texture.h"
#include "gl_core_4_5.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* name, std::string dir)
{
	this->name = name;

	// Create and bind texture ID
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Set Wrapping mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load Image and generate mipmaps
	int width, height, nrChannels;
	unsigned char* data = stbi_load(dir.c_str(), &width, &height, &nrChannels, 0);

	//std::cout << "Texture: " << dir << " width: " << width << " height: " << height << " channel count: " << nrChannels << std::endl;
	
	if (data)
	{
		//if (nrChannels > 1)
			glTexImage2D(GL_TEXTURE_2D, 0, nrChannels != 4 ? GL_RGB : GL_RGBA, width, height, 0, nrChannels != 4 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);
		//else
			//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_STENCIL, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		printf("Failed to load texture\n");
	}
	stbi_image_free(data);
}

Texture::Texture(const char* name, unsigned int id)
{
	this->name = name;
	this->textureID = id;
}

Texture::Texture(const char* name, unsigned int* id)
{
	this->name = name;
	this->textureID = *id;
}

Texture::~Texture()
{

}

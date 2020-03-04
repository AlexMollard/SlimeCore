#pragma once
#include <string>
#include "Types.h"

class Texture
{
public:
	Texture(std::string name, std::string dir);
	Texture(std::string name, unsigned int id);
	Texture(std::string name, unsigned int *id);
	Texture(std::string name);
	~Texture();

	std::string name = "Default Name";
	unsigned int textureID = 0;
};


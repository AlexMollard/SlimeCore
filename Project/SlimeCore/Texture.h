#pragma once
#include <string>
#include <iostream>
#include "Types.h"

class Texture
{
public:
	Texture(const char* name, std::string dir);
	Texture(const char* name, unsigned int id);
	Texture(const char* name, unsigned int *id);
	~Texture();

	const char* name = "Default Name";
	unsigned int textureID = 0;
};


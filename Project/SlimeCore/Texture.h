#pragma once
#include <string>
#include <iostream>
#include "glfw3.h"



class Texture
{
public:
	Texture(std::string dir);
	~Texture();

	unsigned int textureID = 0;
};


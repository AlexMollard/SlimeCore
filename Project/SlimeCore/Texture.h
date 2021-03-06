#pragma once
#include <string>
#include "Types.h"
#include <gl_core_4_5.h>
class Texture
{
public:
	Texture(std::string name, std::string dir);
	Texture(std::string name, unsigned int id);
	Texture(std::string name, unsigned int* id);
	Texture(std::string name);
	Texture() {};
	~Texture();

	void load(std::string dir);
	void Bind() { glBindTexture(GL_TEXTURE_2D, textureID); };
	unsigned int GetID() { return textureID; };
	void SetID(unsigned int newID) { textureID = newID; };
	std::string GetName() { return name; };
	const char* GetNameC() { return name.c_str(); };
protected:
	std::string name = "Default Name";
	unsigned int textureID = 0;
};

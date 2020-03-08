#pragma once
#include "glm.hpp"
#include "Texture.h"

class Material
{
public:

	// Constructors (Subject to change)
	//-----------------
	Material(std::string name, Texture* diffuse, Texture* specMap, Texture* normalMap, Texture* ambientMap, Texture* roughMap);
	Material(std::string name, Texture* diffuse, float diffuseStrength, Texture* specMap, float specularStrength, Texture* normalMap, float normalStrength, Texture* ambientMap, float ambientStrength, Texture* roughMap, float roughStrength);
	Material(std::string name, Texture* diffuse);
	
	virtual ~Material();

	// Textures
	//----------------
	// Set
	void SetDiffuse(Texture* newDiffuse);
	void SetSpecMap(Texture* newSpecular);
	void SetNormalMap(Texture* newNormal);
	void SetAmbientMap(Texture* newAmbient);
	void SetRoughMap(Texture* newRough);

	// Get
	Texture* GetDiffuse();
	Texture* GetSpecMap();
	Texture* GetNormalMap();
	Texture* GetAmbientMap();
	Texture* GetRoughMap();

	// Texture Strengths
	//----------------
	// Set
	void SetDiffuseStrength(float value) { diffuseStrength = value; }
	void SetSpecularStrength(float value) { specularStrength = value; }
	void SetNormalStrength(float value) { normalStrength = value; }
	void SetAmbientStrength(float value) { ambientStrength = value; }
	void SetRoughStrength(float value) { roughStrength = value; }

	// Get
	float GetDiffuseStrength() { return diffuseStrength; }
	float GetSpecularStrength() { return specularStrength; }
	float GetNormalStrength() { return normalStrength; }
	float GetAmbientStrength() { return ambientStrength; }
	float GetRoughStrength() { return roughStrength; }

	// Material Attributes (Outdated mainly used in phong lighting)
	// -------------------
	void setShininess(float newShininess) { shininess = newShininess; }
	float GetShininess() { return shininess; }

	// DirectionalLight (Needs to be made into own class)
	//------------------
	glm::vec3 dirLightDirection = glm::vec3(-0.2f, -1.0f, -0.3f);
	glm::vec3 dirLightAmbient = glm::vec3(0.2f);
	glm::vec3 dirLightDiffuse = glm::vec3(1.0, 0.75, 0.5);
	glm::vec3 dirLightSpecular = glm::vec3(1.0f);

	void SetDirectionalLightAttributes(glm::vec3 newDirection = glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3 newAmbient = glm::vec3(0.2f), glm::vec3 newDiffuse = glm::vec3(0.5f), glm::vec3 newSpecular = glm::vec3(1.0f));
	void SetDirectionalLightDirection(glm::vec3 newDirection) { dirLightDirection = newDirection; }
	void SetDirectionalLightAmbient(glm::vec3 newAmbient) { dirLightAmbient = newAmbient; }
	void SetDirectionalLightDiffuse(glm::vec3 newDiffuse) { dirLightDiffuse = newDiffuse; }
	void SetDirectionalLightSpecular(glm::vec3 newSpecular) { dirLightSpecular = newSpecular; }

	// Misc Functions
	//------------------
	void SetName(std::string newName) { name = newName; }
	std::string GetName() { return name.c_str(); }

protected:
	// Misc
	std::string name = "DefaultName";

	// Phong Lighting variables
	float shininess = 1.0f;

	// Has Bools
	bool hasSpecMap = false;
	bool hasNormalMap = false;
	bool hasSpecColorMap = false;
	bool hasRoughMap = false;

	// Texture Strengths
	float diffuseStrength = 1.0f;
	float specularStrength = 1.0f;
	float normalStrength = 1.0f;
	float ambientStrength = 1.0f;
	float roughStrength = 1.0f;

	// TextureMaps
	Texture* diffuse = nullptr;
	Texture* specMap = nullptr;
	Texture* normalMap = nullptr;
	Texture* ambientMap = nullptr;
	Texture* roughMap = nullptr;
};
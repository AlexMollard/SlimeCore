#pragma once
#include "GameObject.h"
class DirectionalLight : public GameObject
{
public:
	DirectionalLight(std::string name, glm::vec3 pos);
	~DirectionalLight();

	// DirectionalLight (Needs to be made into own class)
	//------------------
	glm::vec3 dirLightDirection = glm::vec3(-0.2f, -1.0f, -0.3f);
	glm::vec3 dirLightAmbient = glm::vec3(0.2f);
	glm::vec3 dirLightAlbedo = glm::vec3(1.0, 0.75, 0.5);
	glm::vec3 dirLightSpecular = glm::vec3(1.0f);

	void SetDirectionalLightAttributes(glm::vec3 newDirection = glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3 newAmbient = glm::vec3(0.2f), glm::vec3 newAlbedo = glm::vec3(0.5f), glm::vec3 newSpecular = glm::vec3(1.0f));
	void SetDirectionalLightDirection(glm::vec3 newDirection) { dirLightDirection = newDirection; }
	void SetDirectionalLightAmbient(glm::vec3 newAmbient) { dirLightAmbient = newAmbient; }
	void SetDirectionalLightAlbedo(glm::vec3 newAlbedo) { dirLightAlbedo = newAlbedo; }
	void SetDirectionalLightSpecular(glm::vec3 newSpecular) { dirLightSpecular = newSpecular; }
};
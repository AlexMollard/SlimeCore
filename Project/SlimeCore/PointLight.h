#pragma once
#include "GameObject.h"
class PointLight : public GameObject
{
public:
	PointLight(std::string name, glm::vec3 pos);
	~PointLight();

	glm::vec3 lightPosition = glm::vec3(0, 1, 0);
	glm::vec3 lightAmbient = glm::vec3(1);
	glm::vec3 lightDiffuse = glm::vec3(1);
	glm::vec3 lightSpecular = glm::vec3(1);

	float lightConstant = 1.0f;
	float lightLinear = 0.09f;
	float lightQuadratic = 0.032f;

	void SetLightAttributes(glm::vec3 newAmbient = glm::vec3(0.2f), glm::vec3 newDiffuse = glm::vec3(1.0f), glm::vec3 newSpecular = glm::vec3(1.0f), float newConstant = 1.0f, float newLinear = 0.09f, float newQuadratic = 0.032f);
	void SetLightAmbient(glm::vec3 newAmbient) { lightAmbient = newAmbient; }
	void SetLightDiffuse(glm::vec3 newDiffuse) { lightDiffuse = newDiffuse; }
	void SetLightSpecular(glm::vec3 newSpecular) { lightSpecular = newSpecular; }

	void SetLightConstant(float newLightConstant) { lightConstant = newLightConstant; }
	void SetLightLinear(float newLightLinear) { lightLinear = newLightLinear; }
	void SetLightQuadratic(float newLightQuadratic) { lightQuadratic = newLightQuadratic; }
};


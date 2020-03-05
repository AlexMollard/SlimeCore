#include "PointLight.h"

PointLight::PointLight(std::string name, glm::vec3 pos)
{
	SetName(name);
	SetPos(pos);
	SetLightAttributes();
}

PointLight::~PointLight()
{

}

void PointLight::SetLightAttributes(glm::vec3 newAmbient, glm::vec3 newDiffuse, glm::vec3 newSpecular, float newConstant, float newLinear, float newQuadratic)
{
	SetLightAmbient(newAmbient);
	SetLightDiffuse(newDiffuse);
	SetLightSpecular(newSpecular);

	SetLightConstant(newConstant);
	SetLightLinear(newLinear);
	SetLightQuadratic(newQuadratic);
}
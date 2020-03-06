#include "PointLight.h"

PointLight::PointLight(std::string name, glm::vec3 pos)
{
	SetName(name);
	SetPos(pos);
	SetAttributes();
}

PointLight::~PointLight()
{

}

void PointLight::SetAttributes(glm::vec3 newAmbient, glm::vec3 newDiffuse, glm::vec3 newSpecular, float newConstant, float newLinear, float newQuadratic)
{
	SetAmbient(newAmbient);
	SetDiffuse(newDiffuse);
	SetSpecular(newSpecular);

	SetConstant(newConstant);
	SetLinear(newLinear);
	SetQuadratic(newQuadratic);
}
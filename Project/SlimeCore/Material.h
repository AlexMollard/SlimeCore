#pragma once
#include "glm.hpp"
#include "ext.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "Shader.h"
#include "Texture.h"

class Material
{
public:
	Material(const char* name, Shader* shader = nullptr, Texture* = nullptr, glm::vec3 newAmbient = glm::vec3(0.2f, 0.05f, 0.04f), glm::vec3 newDiffuse = glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3 newSpecular = glm::vec3(0.5f), float newShininess = 32.0f);
	virtual ~Material();

	Shader* GetShader();
	Texture* GetTexture();
	const char* name = "DefaultName";


	// Materials
	glm::vec3 ambient = glm::vec3(1);
	glm::vec3 diffuseColor = glm::vec3(1);
	glm::vec3 specular = glm::vec3(1);
	float shininess = 1.0f;

	void setMatAtrributes(glm::vec3 newAmbient = glm::vec3(0.4f, 0.05f, 0.14f), glm::vec3 newDiffuseColor = glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3 newSpecular = glm::vec3(0.5f), float newShininess = 32.0f);
	void setAmbient(glm::vec3 newAmbient)			{ ambient = newAmbient;		};
	void setDiffuseColor(glm::vec3 newDiffuseColor)	{ diffuseColor = newDiffuseColor;};
	void setSpecular(glm::vec3 newSpecular)			{ specular = newSpecular;	};
	void setShininess(float newShininess)			{ shininess = newShininess; };

	// SpotLight
	struct PointLight
	{
		PointLight() { SetLightAttributes(); };

		glm::vec3 lightPosition = glm::vec3(0, 1, 0);
		glm::vec3 lightAmbient = glm::vec3(1);
		glm::vec3 lightDiffuse = glm::vec3(1);
		glm::vec3 lightSpecular = glm::vec3(1);

		float lightConstant = 1.0f;
		float lightLinear = 0.09f;
		float lightQuadratic = 0.032f;

		void SetLightAttributes(glm::vec3 newAmbient = glm::vec3(0.2f), glm::vec3 newDiffuse = glm::vec3(0.5f), glm::vec3 newSpecular = glm::vec3(1.0f), float newConstant = 1.0f, float newLinear = 0.09f, float newQuadratic = 0.032f);
		void SetLightPosition(glm::vec3 newLightPos) { lightPosition = newLightPos; };
		void SetLightAmbient(glm::vec3 newAmbient) { lightAmbient = newAmbient; };
		void SetLightDiffuse(glm::vec3 newDiffuse) { lightDiffuse = newDiffuse; };
		void SetLightSpecular(glm::vec3 newSpecular) { lightSpecular = newSpecular; };

		void SetLightConstant(float newLightConstant) { lightConstant = newLightConstant; };
		void SetLightLinear(float newLightLinear) { lightLinear = newLightLinear; };
		void SetLightQuadratic(float newLightQuadratic) { lightQuadratic = newLightQuadratic; };
	};
	PointLight pointLights[4];


	// DirectionalLight
	glm::vec3 dirLightDirection = glm::vec3(-0.2f, -1.0f, -0.3f);

	glm::vec3 dirLightAmbient = glm::vec3(0.2f);
	glm::vec3 dirLightDiffuse = glm::vec3(1.0, 0.75, 0.5);
	glm::vec3 dirLightSpecular = glm::vec3(1.0f);
	
	void SetDirectionalLightAttributes(glm::vec3 newDirection = glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3 newAmbient = glm::vec3(0.2f), glm::vec3 newDiffuse = glm::vec3(0.5f), glm::vec3 newSpecular = glm::vec3(1.0f));
	void SetDirectionalLightDirection(glm::vec3 newDirection) { dirLightDirection = newDirection; };
	void SetDirectionalLightAmbient(glm::vec3 newAmbient) { dirLightAmbient = newAmbient; };
	void SetDirectionalLightDiffuse(glm::vec3 newDiffuse) { dirLightDiffuse = newDiffuse; };
	void SetDirectionalLightSpecular(glm::vec3 newSpecular) { dirLightSpecular = newSpecular; };
protected:
	Shader* shader = nullptr;
	Texture* texture = nullptr;
	bool hasOwnTexture = false;
};


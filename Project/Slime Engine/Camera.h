#pragma once
#include "glm.hpp"
#include "ext.hpp"
class Camera
{
	glm::mat4 worldTransform;
	glm::mat4 viewTransform = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 projectionTransform = glm::perspective(1.5f, 16 / 9.0f, 0.01f, 10.0f);
	glm::mat4 projectionViewTransform;

public:
	glm::vec3 position = glm::vec3(0);
	Camera(glm::vec3 position = glm::vec3(0.0f, 1.0f, 0.0f));

	void Update(float deltaTime = 0);
	void SetPerspective(float fieldOfView, float aspectRatio, float near, float far);
	void SetLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	void SetPosition(glm::vec3 position);
	glm::mat4 GetWorldTransform();
	glm::mat4 GetView();
	glm::mat4 GetProjection();
	void SetProjection(glm::mat4 newProjection);
	glm::mat4 GetProjectionView();
	void UpdateProjectionViewTransform();
};
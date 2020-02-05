#pragma once
#include "glm.hpp"
#include "ext.hpp"

#include <vector>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = -15.0f;
const float SPEED = 10.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	float Yaw;
	float Pitch;

	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	glm::mat4 worldTransform;
	glm::mat4 viewTransform = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 projectionTransform = glm::perspective(1.5f, 16 / 9.0f, 0.01f, 10.0f);
	glm::mat4 projectionViewTransform;

	glm::vec3 position = glm::vec3(0);
	Camera(glm::vec3 position = glm::vec3(0.0f, 1.0f, 0.0f));

	virtual void Update(float deltaTime) = 0;
	void SetPerspective(float fieldOfView, float aspectRatio, float near, float far);
	void SetLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	void SetPosition(glm::vec3 position);
	glm::mat4 GetWorldTransform();
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjection();
	void SetProjection(glm::mat4 newProjection);
	glm::mat4 GetProjectionView();
	void UpdateProjectionViewTransform();
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
	void updateCameraVectors();
};
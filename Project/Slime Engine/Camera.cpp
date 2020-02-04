#include "Camera.h"

Camera::Camera(glm::vec3 position)
{
	SetPosition(position);
	UpdateProjectionViewTransform();
}

void Camera::Update(float deltaTime)
{
}

void Camera::SetPerspective(float fieldOfView, float aspectRatio, float, float)
{
}

void Camera::SetLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{
}

void Camera::SetPosition(glm::vec3 position)
{
	
}

glm::mat4 Camera::GetWorldTransform()
{
	return worldTransform;
}

glm::mat4 Camera::GetView()
{
	return viewTransform;
}

glm::mat4 Camera::GetProjection()
{
	return projectionTransform;
}

void Camera::SetProjection(glm::mat4 newProjection)
{
	projectionTransform = newProjection;
}

glm::mat4 Camera::GetProjectionView()
{
	return projectionViewTransform;
}

void Camera::UpdateProjectionViewTransform()
{
	projectionViewTransform = projectionTransform * viewTransform;
}

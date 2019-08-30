#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

void Camera::AddYaw(float Angle)
{
	Yaw += Angle;
}

void Camera::AddPitch(float Angle)
{
	Pitch += Angle;
	Pitch = glm::clamp(Pitch, -85.f, 85.f);
}

glm::vec3 Camera::GetRightVector()
{
	return glm::normalize(glm::cross(GetForwardVector(), glm::vec3(0.f, 1.f, 0.f)));
}

glm::vec3 Camera::GetForwardVector()
{
	glm::quat YawQuat = glm::angleAxis(glm::radians(Yaw), glm::vec3(0.f, 1.f, 0.f));
	glm::quat PitchQuat = glm::angleAxis(glm::radians(Pitch), glm::vec3(1.f, 0.f, 0.f));
	return (YawQuat * PitchQuat) * glm::vec3(0.f, 0.f, -1.f);
}

glm::mat4 Camera::GetViewMatrix()
{	
	return glm::lookAt(Position, Position + GetForwardVector(), glm::vec3(0.f, 1.f, 0.f));
}

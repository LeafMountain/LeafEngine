#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	void AddYaw(float YawAngle);
	void AddPitch(float PitchAngle);

	glm::vec3 GetRightVector();
	glm::vec3 Position = glm::vec3(0.f);
	//glm::vec3 Direction = glm::vec3(0.f, 0.f, -1.f);
	float Yaw = 0.f;
	float Pitch = 0.f;


	glm::vec3 GetForwardVector();
	glm::mat4 GetViewMatrix();
};
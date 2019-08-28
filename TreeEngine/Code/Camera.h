#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	glm::vec3 Position = glm::vec3(0.f);
	glm::vec3 Direction = glm::vec3(0.f, 0.f, -1.f);

	glm::mat4 GetViewMatrix();
};
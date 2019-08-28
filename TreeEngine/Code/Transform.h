#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class Transform
{
public:
	glm::vec3 Position = glm::vec3(0.f);
	glm::quat Rotation = glm::identity<glm::quat>();
	glm::vec3 Scale = glm::vec3(1.f);

	glm::mat4 GetMatrix();
};
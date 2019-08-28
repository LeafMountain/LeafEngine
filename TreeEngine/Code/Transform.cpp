#include "Transform.h"

glm::mat4 Transform::GetMatrix()
{
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(1.f), Scale);
	glm::mat4 RotationMatrix = (glm::mat4)Rotation;
	glm::mat4 PositionMatrix = glm::translate(glm::mat4(1.f), Position);

	return PositionMatrix * RotationMatrix * ScaleMatrix;
}

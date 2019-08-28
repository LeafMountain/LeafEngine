#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Camera::GetViewMatrix()
{	
	return glm::lookAt(Position, Position + Direction, glm::vec3(0.f, 1.f, 0.f));
}

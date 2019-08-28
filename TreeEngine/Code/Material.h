#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

class Material
{
public:
	void LoadFile(const char* VertexPath, const char* FragmentPath);
	void Use();
	void Set(const char* name, const glm::mat4& value);

	GLuint ProgramHandle;
};
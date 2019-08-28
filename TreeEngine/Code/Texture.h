#pragma once
#include <GL/glew.h>

class Texture
{
public:
	void LoadFile(const char* File);
	void Bind();

	GLuint Handle;
};
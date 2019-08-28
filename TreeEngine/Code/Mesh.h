#pragma once
#include <GL\glew.h>


class Mesh
{
public:
	void LoadVerts(const float* Verts, int Size);
	void Bind();

	GLuint VertexObject;
	GLuint Buffer;
};
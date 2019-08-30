#pragma once
#include <GL\glew.h>
#include <fstream>

class Mesh
{
public:
	void LoadVerts(const float* Verts, int VertSize, const unsigned int* Indicies, int IndexSize);
	void Bind();

	void LoadFile(const char* Path);

	GLuint VertexObject;
	GLuint Buffer;
	GLuint IndexBuffer;

	GLuint Triangles;
};
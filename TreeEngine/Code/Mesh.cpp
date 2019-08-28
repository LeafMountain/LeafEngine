#include "Mesh.h"

void Mesh::LoadVerts(const float* Verts, int Size)
{
	glGenBuffers(1, &VertexObject);
	glBindVertexArray(VertexObject);

	glGenBuffers(1, &Buffer);
	glBindBuffer(GL_ARRAY_BUFFER, Buffer);
	glBufferData(GL_ARRAY_BUFFER, Size, Verts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, (3 + 2) * sizeof(float), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, (3 + 2) * sizeof(float), (void*)((3) * sizeof(float)));

	glBindVertexArray(0);
}

void Mesh::Bind()
{
	glBindVertexArray(VertexObject);
}

#include "Mesh.h"
#include <sstream>
#include <string>
#include <glm/glm.hpp>

using namespace std;

void Mesh::LoadVerts(const float* Verts, int VertSize, const unsigned int* Indicies, int IndexSize)
{
	glGenVertexArrays(1, &VertexObject);
	glBindVertexArray(VertexObject);

	// Load vertex data
	glGenBuffers(1, &Buffer);
	glBindBuffer(GL_ARRAY_BUFFER, Buffer);
	glBufferData(GL_ARRAY_BUFFER, VertSize, Verts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, (3 + 3 + 2) * sizeof(float), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, (3 + 3 + 2) * sizeof(float), (void*)((3) * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, false, (3 + 3 + 2) * sizeof(float), (void*)((6) * sizeof(float)));

	// Load index data
	if (Indicies != nullptr)
	{
		glGenBuffers(1, &IndexBuffer);
		// try using the index buffer to see if it works
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexSize, Indicies, GL_STATIC_DRAW);
	}

	glBindVertexArray(0);
}

void Mesh::Bind()
{
	glBindVertexArray(VertexObject);
}

void Mesh::LoadFile(const char* Path)
{
	ifstream MeshFile(Path);
	std::string Line;

	float Verts[10000];
	unsigned int Indices[10000];

	int VertsIndex = 0;
	int IndexIndex = 0;

	bool temp = false;

	while (getline(MeshFile, Line))
	{
		//printf("%s\n", Line.c_str());
		if (Line.find("vt", 0, 2) != string::npos)	// It's a UV
		{
		}
		else if (Line.find("vn", 0, 1) != string::npos) // It's a Normal
		{
		}
		else if (Line.find("v", 0, 1) != string::npos) // It's an Position
		{
			if (temp)
			{
				istringstream temp(Line);
				string type;
				float x, y, z;
				temp >> type >> x >> y >> z;
				//printf("%f\n", Position.x);

				// Position
				Verts[VertsIndex] = x;
				Verts[VertsIndex + 1] = y;
				Verts[VertsIndex + 2] = z;

				// Normal
				Verts[VertsIndex + 3] = 0.f;
				Verts[VertsIndex + 4] = 0.f;
				Verts[VertsIndex + 5] = 0.f;

				// UV
				Verts[VertsIndex + 6] = 0.f;
				Verts[VertsIndex + 7] = 0.f;

				VertsIndex += 7;
			}
			else
			{
				temp = true;
			}
		}
		else if (Line == "f", 0, 1) // It's an Index
		{
			istringstream temp(Line);
			string type;
			int x, y, z;
			temp >> type >> x >> y >> z;

			Indices[IndexIndex] = x;
			Indices[IndexIndex + 1] = y;
			Indices[IndexIndex + 2] = z;

			IndexIndex += 3;
		}
	}

	Triangles = IndexIndex / 3;
	LoadVerts(Verts, sizeof(Verts), nullptr, 0);
}

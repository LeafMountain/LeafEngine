#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <fstream>

using namespace std;

const char* VERTEX_SRC = R"(
#version 330 core
in vec2 a_Position;
in vec3 a_Color;

out vec3 f_Color;

void main()
{
	gl_Position = vec4(a_Position, 0.0, 1.0);
	f_Color = a_Color;
}
)";

const char* FRAGMENT_SRC = R"(
#version 330 core
in vec3 f_Color;
out vec4 o_Color;

void main()
{
	o_Color = vec4(f_Color, 1.0);
}
)";

bool shouldQuit = false;

void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		printf("OnKeyEvent( %d )\n", key);
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		printf("Close\n");
		shouldQuit = true;
	}
}

//int LoadShader(char* filename, GLchar** shaderSource, unsigned long* length)
//{
//	ifstream file;
//	file.open(filename, ios::in);
//	if (!file) return -1;
//
//	length = file
//
//	*shaderSource = (GLubyte*) new char[length + 1];
//}

int main()
{
	// Create a window and context
	glfwInit();

	GLFWwindow* window;
	window = glfwCreateWindow(800, 600, "This is OpenGL", nullptr, nullptr);

	glfwSetKeyCallback(window, OnKeyEvent);
	glfwMakeContextCurrent(window);

	// Import OpenGL extensions, through the extensions wrangler
	glewInit();

	// Vertex POSITIONS //
	// Create a VBO (Vertex Buffer Object), to contain our triangles
	GLuint positionBuffer = 0;
	glCreateBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	// Fill the VBO with data
	float verts[] =
	{
		-0.5, -0.5f,
		0.5f, -0.5,
		0.f, 0.5f
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	// Enable and bind our VBO to an attribute
	// Tell Opengl that our VBO contains floats and that vertices are grouped two floats at a time
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);

	/* COLOR */
	GLuint colorBuffer = 0;
	glCreateBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);

	// Fill the VBO with data
	float colors[] =
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, 0);
		
	printf("Hey good looking !\n");

	glClearColor(0.f, 0.6f, 0.5f, 1.f);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &VERTEX_SRC, nullptr);
	glShaderSource(fragmentShader, 1, &FRAGMENT_SRC, nullptr);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);
	
	// Make and link shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// Show to log of the shader program
	char infoLogBuffer[1024];
	glGetProgramInfoLog(shaderProgram, 1024, nullptr, infoLogBuffer);
	printf("SHADER RESULT: \n%s\n", infoLogBuffer);

	// Set the trianglecolor in the shader
	//GLuint triangleColor = glGetUniformLocation(shaderProgram, "u_TriangleColor");

	while (!glfwWindowShouldClose(window) && !shouldQuit)
	{
		//double mouseX = 0;
		//double mouseY = 0;
		//glfwGetCursorPos(window, &mouseX, &mouseY);
		//verts[4] = mouseX;
		//verts[5] = mouseY;
		//
		//float sinTime = sin(glfwGetTime()) * 0.5f + 0.5f;
		//glUniform4f(triangleColor, ((float)mouseY / 600 * - 1) + 600, (float)mouseY / 600, (float)mouseX / 800, 1.0f);

		// Clear screen
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw triangle
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);

		// Swap back-buffer to the front and poll and handle window events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}
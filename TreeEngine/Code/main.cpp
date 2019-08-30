#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Material.h"
#include "Mesh.h"
#include "Transform.h"
#include "Texture.h"
#include "Camera.h"

bool shouldQuit = false;
bool KeyState[GLFW_KEY_LAST] = { false };

bool LeftMousePressed = false;

const float CubeVertexData[] =
{
	// Front face
	-1.f, -1.f, 1.f,	0.f, 0.f, 1.f,	0.f, 0.f,
	1.f, -1.f, 1.f,		0.f, 0.f, 1.f,	1.f, 0.f,
	1.f, 1.f, 1.f,		0.f, 0.f, 1.f,	1.f, 1.f,
	-1.f, 1.f, 1.f,		0.f, 0.f, 1.f,	0.f, 1.f,

	// Back face
	-1.f, -1.f, -1.f,	0.f, 0.f, -1.f,	0.f, 0.f,
	1.f, -1.f, -1.f,	0.f, 0.f, -1.f,	1.f, 0.f,
	1.f, 1.f, -1.f,		0.f, 0.f, -1.f,	1.f, 1.f,
	-1.f, 1.f, -1.f,	0.f, 0.f, -1.f,	0.f, 1.f,

	// Right face
	-1.f, -1.f, -1.f,	0.f, 0.f, -1.f,	0.f, 0.f,
	1.f, -1.f, -1.f,	0.f, 0.f, -1.f,	1.f, 0.f,
	1.f, 1.f, -1.f,		0.f, 0.f, -1.f,	1.f, 1.f,
	-1.f, 1.f, -1.f,	0.f, 0.f, -1.f,	0.f, 1.f,
};

const unsigned int CubeIndexData[] =
{
	// Front face
	0, 1, 2,	0, 2, 3,

	// Back face
	4, 5, 6,	4, 6, 7,

	// Top face
	7, 4, 3,	7, 3, 6
};

bool IsKeyPressed(int Key)
{
	return KeyState[Key];
}

void OnKeyEvent(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
	if (Action == GLFW_REPEAT)
		return;

	KeyState[Key] = (Action == GLFW_PRESS);

	if (Action == GLFW_PRESS)
	{
		printf("OnKeyEvent( %d )\n", Key);

		if (Key == GLFW_KEY_ESCAPE)
		{
			printf("Close\n");
			shouldQuit = true;
		}
	}
}

void OnMouseButton(GLFWwindow* Window, int Button, int Action, int Mods)
{
	if (Button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		LeftMousePressed = Action == GLFW_PRESS;
		glfwSetInputMode(Window, GLFW_CURSOR, LeftMousePressed ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
	}
}

int main()
{
	// Create a window and context
	glfwInit();

	GLFWwindow* Window;
	Window = glfwCreateWindow(800, 800, "This is OpenGL", nullptr, nullptr);

	glfwSetKeyCallback(Window, OnKeyEvent);
	glfwMakeContextCurrent(Window);

	// Import OpenGL extensions, through the extensions wrangler
	glewInit();

// VERTEX STUFF //
	// TRIANGLE
	float TriData[]
	{
		-0.5f, -0.5f,0.f,	0.f, 0.f, 1.f,	0.f, 0.f,
		0.5f, -0.5f, 0.f,	0.f, 0.f, 1.f,	1.f, 0.f,
		0.f, 0.5f, 0.f,		0.f, 0.f, 1.f,	0.5f, 1.f
	};

	Mesh TriangleMesh;
	TriangleMesh.LoadVerts(TriData, sizeof(TriData), nullptr, 0);
	
	// QUAD
	float QuadData[]
	{
		-0.5f, -0.5f, 0.f,	0.f, 0.f, 1.f,	0.f, 0.f,
		0.5f, -0.5f, 0.f,	0.f, 0.f, 1.f,	1.f, 0.f,
		-0.5f, 0.5f, 0.f,	0.f, 0.f, 1.f,	0.f, 1.f,
		0.5f, 0.5f, 0.f,	0.f, 0.f, 1.f,	1.f, 1.f,
	};

	Mesh QuadMesh;
	QuadMesh.LoadVerts(QuadData, sizeof(QuadData), nullptr, 0);

	Mesh CubeMesh;
	CubeMesh.LoadVerts(CubeVertexData, sizeof(CubeVertexData), CubeIndexData, sizeof(CubeIndexData));

	Mesh DeerMesh;
	DeerMesh.LoadFile("Res/deer.obj");


// UNIFORMS

	Material DefaultMaterial;
	DefaultMaterial.LoadFile("Res/Shaders/default.vert", "Res/Shaders/default.frag");
	DefaultMaterial.Use();

	Texture MyTexture;
	MyTexture.LoadFile("Res/Image.jpg");
	MyTexture.Bind();

	// Transforms
	Transform Transforms[4];
	Transforms[0].Position = glm::vec3(0.f);
	Transforms[1].Position = glm::vec3(2.f, 0.f, -1.f);
	Transforms[2].Position = glm::vec3(4.f, 0.f, -2.f);
	Transforms[2].Scale = glm::vec3(1.f) * 0.1f;

	DefaultMaterial.Set("u_LightDirection", glm::vec3(0.f, -1.f, 0.f));

	// Camera
	Camera Cam;
	Cam.Position = glm::vec3(0.f, 0.f, 5.f);

	float Ratio = 1024.f / 600.f;
	glm::mat4 Projection;
	Projection = glm::perspective(glm::radians(60.f), Ratio, 0.2f, 100.f);
	DefaultMaterial.Set("u_Projection", Projection);

	glEnable(GL_DEPTH_TEST);

	glClearColor(0.1f, 0.1f, 0.1f, 1.f);

	float LastFrameTime = 0.f;

	glfwSetCursorPos(Window, 0, 0);
	glfwSetMouseButtonCallback(Window, OnMouseButton);

	while (!glfwWindowShouldClose(Window) && !shouldQuit)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float DeltaTime = glfwGetTime() - LastFrameTime;
		LastFrameTime = glfwGetTime();

		double MouseX = 0;
		double MouseY = 0;
		glfwGetCursorPos(Window, &MouseX, &MouseY);

		if (LeftMousePressed == true)
		{
			glm::vec3 Velocity = glm::vec3(0.f);

			Velocity += IsKeyPressed(GLFW_KEY_W) ? Cam.GetForwardVector() : glm::vec3(0.f);
			Velocity += IsKeyPressed(GLFW_KEY_S) ? -Cam.GetForwardVector() : glm::vec3(0.f);
			Velocity += IsKeyPressed(GLFW_KEY_A) ? -Cam.GetRightVector() : glm::vec3(0.f);
			Velocity += IsKeyPressed(GLFW_KEY_D) ? Cam.GetRightVector() : glm::vec3(0.f);
		
			if (IsKeyPressed(GLFW_KEY_SPACE)) Velocity += glm::vec3(0.f, 1.f, 0.f);
			if (IsKeyPressed(GLFW_KEY_C)) Velocity -= glm::vec3(0.f, 1.f, 0.f);

			float Speed = 5;
			Velocity *= DeltaTime * Speed;

			Cam.Position += Velocity;

			float MouseSensitivity = 2.f;
			Cam.AddYaw(-MouseX * DeltaTime * MouseSensitivity);
			Cam.AddPitch(-MouseY * DeltaTime * MouseSensitivity);

			// Reset mouse
			glfwSetCursorPos(Window, 0, 0);
		}

		// Set view
		DefaultMaterial.Set("u_View", Cam.GetViewMatrix());

		// Rotate cube
		glm::quat DeltaRotation = glm::angleAxis(glm::radians(90.f) * DeltaTime, glm::normalize(glm::vec3(1.f, 1.f, 0.f)));

		for (int i = 0; i < 3; i++)
		{
			Transforms[i].Rotation *= DeltaRotation;
		}
		
		// Draw cube
		//CubeMesh.Bind();
		//DefaultMaterial.Set("u_World", Transforms[0].GetMatrix());
		//glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

		// Draw quad
		QuadMesh.Bind();
		DefaultMaterial.Set("u_World", Transforms[1].GetMatrix());
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		// Draw triangle
		//TriangleMesh.Bind();
		//DefaultMaterial.Set("u_World", Transforms[2].GetMatrix());
		//glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);

		DeerMesh.Bind();
		DefaultMaterial.Set("u_World", Transforms[2].GetMatrix());
		glDrawArrays(GL_TRIANGLES, 0, DeerMesh.Triangles);


		// Swap buffers
		glfwSwapBuffers(Window);
		glfwPollEvents();
	}

	return 0;
}
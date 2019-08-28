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
		-0.5f, -0.5f,0.f,	0.f, 0.f,
		0.5f, -0.5f, 0.f,	1.f, 0.f,
		0.f, 0.5f, 0.f,		0.5f, 1.f
	};

	Mesh TriangleMesh;
	TriangleMesh.LoadVerts(TriData, sizeof(TriData));
	
	// QUAD
	float QuadData[]
	{
		-0.5f, -0.5f, 0.f,	0.f, 0.f,
		0.5f, -0.5f, 0.f,	1.f, 0.f,
		0.5f, 0.5f, 0.f,	1.f, 1.f,
		-0.5f, 0.5f, 0.f,	0.f, 1.f
	};

	Mesh QuadMesh;
	QuadMesh.LoadVerts(QuadData, sizeof(QuadData));


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
	Transforms[1].Position = glm::vec3(1.5f, 0.f, 0.f);
	Transforms[2].Position = glm::vec3(3.f, 0.f, 0.f);
	Transforms[3].Position = glm::vec3(-3.f, 0.f, 0.f);


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

	glfwGetCursorPos(Window, 0, 0);
	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	while (!glfwWindowShouldClose(Window) && !shouldQuit)
	{
		float DeltaTime = LastFrameTime - glfwGetTime();
		LastFrameTime = glfwGetTime();


		glm::vec3 Velocity = glm::vec3(0.f);
		Velocity -= Cam.Direction;

		//Velocity.z += IsKeyPressed(GLFW_KEY_W) ? 1 : 0;
		//Velocity.z += IsKeyPressed(GLFW_KEY_S) ? -1 : 0;
		//Velocity.x += IsKeyPressed(GLFW_KEY_A) ? 1 : 0;
		//Velocity.x += IsKeyPressed(GLFW_KEY_D) ? -1 : 0;


		
		float Speed = 1;
		Velocity *= DeltaTime * Speed;

		Cam.Position += Velocity;

		double MouseX = 0;
		double MouseY = 0;
		glfwGetCursorPos(Window, &MouseX, &MouseY);

		glm::vec3 CameraDirection = Cam.Direction;
		CameraDirection = glm::vec3(cos(CameraDirection.x * MouseX) - sin(CameraDirection.z * MouseX), 0, 0) * DeltaTime;
		CameraDirection = glm::normalize(CameraDirection);
		Cam.Direction = CameraDirection;

		// Reset mouse
		glfwSetCursorPos(Window, 0, 0);

		DefaultMaterial.Set("u_View", Cam.GetViewMatrix());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		QuadMesh.Bind();

		for (int i = 0; i < 3; ++i)
		{
			DefaultMaterial.Set("u_World", Transforms[i].GetMatrix());
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		}

		glfwSwapBuffers(Window);
		glfwPollEvents();
	}

	return 0;
}
GLSL code

--- VERTEX SHADER ---
#version 330 core
in vec2 a_Position;

void main()
{
	gl_Position = a_Position;
}

-----------------------
--- FRAGMENT SHADER ---
#version 330 core
out vec4 o_Color;

void main()
{
	o_Color = vec4(0.6941, 0.1059, 0.2549, 1.0);
}
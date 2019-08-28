#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

uniform float u_Time;
uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_World;

out vec2 f_TexCoord;

void main()
{
	gl_Position = u_Projection * u_View * u_World * vec4(a_Position, 1.0);
	f_TexCoord = a_TexCoord;
}

#version 330 core
uniform sampler2D u_Sampler1;
uniform sampler2D u_Sampler2;

uniform float u_Time;

uniform vec3 u_LightDirection;

in vec2 f_TexCoord;
in vec3 f_Normal;
out vec4 o_Color;

const vec3 DiffuseColor = vec3(0.65, 0.51, 0.0);
const vec3 AmbientColor = vec3(1.0, 0.8, 0.2);

void main()
{
	vec2 TexCoord = f_TexCoord;
	TexCoord.y = 1.0 - TexCoord.y;

	vec4 Image1 = texture(u_Sampler1, TexCoord);
	vec4 Image2 = texture(u_Sampler2, TexCoord);

	// Calculate light
	// Diffuse Lighting
	float Diffuse = max(-dot(u_LightDirection, f_Normal), 0.0);

	// Ambient
	float Ambient = 0.2;

	o_Color = mix(Image1, Image2, sin(u_Time) * 0.5 + 0.5);
	o_Color.xyz *= (DiffuseColor * Diffuse) + (AmbientColor * Ambient);
}

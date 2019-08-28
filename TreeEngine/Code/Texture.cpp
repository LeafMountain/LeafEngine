#include "Texture.h"
#include <SOIL.h>

void Texture::LoadFile(const char* File)
{
	int Width;
	int Height;
	int Channel;
	unsigned char* ImagePixels = SOIL_load_image(File, &Width, &Height, &Channel, SOIL_LOAD_RGBA);

	glGenTextures(1, &Handle);
	glBindTexture(GL_TEXTURE_2D, Handle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ImagePixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // GL_NEREAST = Hard edges
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	SOIL_free_image_data(ImagePixels);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, Handle);
}

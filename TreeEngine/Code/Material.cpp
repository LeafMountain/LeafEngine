#include "Material.h"
#include <cstdio>
#include <glm/gtc/type_ptr.hpp>

GLuint LoadShader(const char* Path, GLenum ShaderType)
{
	GLuint ShaderHandle = glCreateShader(ShaderType);
	//FILE* File = fopen(Path, "r");
	FILE* File;
	fopen_s(&File, Path, "rb");

	if (File == nullptr)
	{
		printf("Shader file '%s' does not exist! \n", Path);
		return ShaderHandle;
	}

	fseek(File, 0, SEEK_END);			// Go to the last element of the file?
	int FileLength = ftell(File);		// Get the index of the current position?
	char* FileContents = new char[FileLength];	
	fseek(File, 0, SEEK_SET);			// Set offset to 0 (to start from the beginning)

	fread(FileContents, 1, FileLength, File);
	fclose(File);

	glShaderSource(ShaderHandle, 1, &FileContents, &FileLength);
	glCompileShader(ShaderHandle);

	delete[] FileContents;
	
	return ShaderHandle;
}

void Material::LoadFile(const char* VertexPath, const char* FragmentPath)
{
	GLuint VertexHandle = LoadShader(VertexPath, GL_VERTEX_SHADER);
	GLuint FragmentHandle = LoadShader(FragmentPath, GL_FRAGMENT_SHADER);

	ProgramHandle = glCreateProgram();
	glAttachShader(ProgramHandle, VertexHandle);
	glAttachShader(ProgramHandle, FragmentHandle);
	glLinkProgram(ProgramHandle);

	glDetachShader(ProgramHandle, VertexHandle);
	glDetachShader(ProgramHandle, FragmentHandle);
	glDeleteShader(VertexHandle);
	glDeleteShader(FragmentHandle);

	GLint LinkStatus;
	glGetProgramiv(ProgramHandle, GL_LINK_STATUS, &LinkStatus);

	if (LinkStatus == GL_FALSE)
	{
		printf("Program failed to link\n");

		char LogBuffer[1024];
		glGetProgramInfoLog(ProgramHandle, 1024, nullptr, LogBuffer);

		printf("%s\n", LogBuffer);
	}
}

void Material::Use()
{
	glUseProgram(ProgramHandle);
}

void Material::Set(const char* name, const glm::mat4& value)
{
	GLuint Location = glGetUniformLocation(ProgramHandle, name);
	glUniformMatrix4fv(Location, 1, false, glm::value_ptr(value));
}

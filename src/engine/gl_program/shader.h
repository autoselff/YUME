#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

struct Shader {
private:
	GLuint id;

public:
	Shader(GLenum sType);
	~Shader();

	const char* sTypeStr() const;
	GLenum sType() const;
	GLuint getId();
	void loadShaderPath(const std::string& path);
	void loadShaderSource(const GLchar* shaderSource);
	void checkCompileErrors();
};

Shader generateShaderPath(GLenum sType, const std::string& path);
Shader generateShaderSource(GLenum sType, const char* sourceCode);
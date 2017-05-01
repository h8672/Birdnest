#include "shader.h"
#include "filereader.h"

Shader::Shader(const GLchar * vertexPath, const GLchar * fragmentPath)
{
	// Vertex shader
	GLchar* shadersource;
	std::string directory = "shaders/";
	directory.append(vertexPath);
	shadersource = FileReader::readfile(directory.c_str());
	std::cout << "Vertex\n" << shadersource << std::endl;

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &shadersource, NULL);
	glCompileShader(vertexShader);
	// Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Vertex shader fail!\n" << infoLog << std::endl;
	}

	// Fragment shader
	directory = "shaders/";
	directory.append(fragmentPath);
	shadersource = FileReader::readfile((directory).c_str());
	std::cout << "Fragment\n" << shadersource << std::endl;

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &shadersource, NULL);
	glCompileShader(fragmentShader);
	// Check for compile time errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Fragment shader fail!\n" << infoLog << std::endl;
	}

	// Link shaders
	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertexShader);
	glAttachShader(this->Program, fragmentShader);
	glLinkProgram(this->Program);
	// Check for linking errors
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Use() {
	glUseProgram(this->Program);
}

#pragma once
#include <glad/glad.h>;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class YRShader
{
public:
	/*
		shaderProgram id
	*/
	unsigned int id;

	/*
		read file from file paths and create vertex shader and fragment shader, then
		link them and generate shader program.
	*/
	YRShader(std::string& vertexShaderFilePath, std::string& fragmentShaderFilePath);

	void use();

	void setBool(const std::string& name, bool value) const;

	void setInt(const std::string& name, int value) const;

	void setFloat(const std::string& name, float value) const;

	void setMat4(const std::string& name, glm::mat4& value) const;

	/*
		create a vertex shader from vertex shader source.
	*/
	unsigned int createVertexShader(const char* vertexShaderSource);

	unsigned int createFragmentShader(const char* fragmentShaderSource);

	unsigned int creatLinkShadersProgram(unsigned int& vertexShader,
		unsigned int& fragmentShader);
};
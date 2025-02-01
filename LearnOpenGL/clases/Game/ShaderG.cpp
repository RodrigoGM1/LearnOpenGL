#include "ShaderG.h"

ShaderG& ShaderG::Use()
{
	glUseProgram(this->ID);
	return *this;
}

void ShaderG::Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource)
{
	unsigned int sVertex, sFragment, gShader;

	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vertexSource, NULL);
	glCompileShader(sVertex);
	checkCompileErrors(sVertex, "VERTEX");

	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragmentSource, NULL);
	glCompileShader(sFragment);
	checkCompileErrors(sFragment, "FRAGMENT");

	if (geometrySource != nullptr) {
		gShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gShader, 1, &geometrySource, NULL);
		glCompileShader(gShader);
		checkCompileErrors(gShader, "GEOMETRY");
	}

	this->ID = glCreateProgram();
	glAttachShader(this->ID, sVertex);
	glAttachShader(this->ID, sFragment);
	if (geometrySource != nullptr) {
		glAttachShader(this->ID, gShader);
	}
	glLinkProgram(this->ID);
	checkCompileErrors(this->ID, "PROGRAMA");

	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
	if (geometrySource != nullptr) { glDeleteShader(gShader); }
}

void ShaderG::SetFloat(const char* name, float value, bool useShader)
{
	if (useShader) { this->Use(); }
	glUniform1f(glGetUniformLocation(this->ID, name), value);
}

void ShaderG::SetInteger(const char* name, int value, bool useShader)
{
	if (useShader) { this->Use(); }
	glUniform1i(glGetUniformLocation(this->ID, name), value);
}

void ShaderG::SetVector2f(const char* name, float x, float y, bool useShader)
{
	if (useShader) { this->Use(); }
	glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}

void ShaderG::SetVector2f(const char* name, const glm::vec2& value, bool useShader)
{
	if (useShader) { this->Use(); }
	glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}

void ShaderG::SetVector3f(const char* name, float x, float y, float z, bool useShader)
{
	if (useShader) { this->Use(); }
	glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}

void ShaderG::SetVector3f(const char* name, const glm::vec3& value, bool useShader)
{
	if (useShader) { this->Use(); }
	glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}

void ShaderG::setVector4f(const char* name, float x, float y, float z, float w, bool useShader)
{
	if (useShader) { this->Use(); }
	glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}

void ShaderG::setVector4f(const char* name, const glm::vec4& value, bool useShader)
{
	if (useShader) { this->Use(); }
	glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}

void ShaderG::checkCompileErrors(unsigned int object, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAMA") {
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Tiempo de compilacion error: Tipo: " << type << "\n" << infoLog << "\n ------------------------------------------" << std::endl;
		}
	}
	else {
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success) {
			std::cout << "| ERROR::SHADER: Tiempo de link: Tipo: " << type << "\n" << infoLog << "\n ------------------------------------------" << std::endl;
		}
	}
}
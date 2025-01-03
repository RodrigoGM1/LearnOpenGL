#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode; // Cadena basica de caracteres char
	std::ifstream vShaderFile;
	std::ifstream fShaderFile; // Clase de flujo de entrada para operar en archivos operaciones de entrada/salida en el archivo al que están asociados.

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit); // Asgurar que los objetos ifstream puedan generar execepciones

	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath); // Se abren los archivos asociados en el arguemto
		std::stringstream vShaderStream, fShaderStream; // Clase de transmisión para operar en cadenas de caracteres

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf(); // Obtener/establecer búfer de flujo

		vShaderFile.close();
		fShaderFile.close(); // Se cierran los archivos asociados en el arguemto

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) { // Si en caso de no abrir archivos 
		std::cout << "ERROR::SHADER::ARCHIVO_NO_ENCONTRADO" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str(); // Devuelve un puntero a una matriz que contiene una secuencia de caracteres terminada en nulo
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::checkCompileErrors(GLuint shader, std::string type)
{
	GLint success;
	GLchar infoLog[1024];

	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILACION_ERROR de tipo" << type << "\n" << infoLog << std::endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_LINKEO_PROGRAMA de tipo" << type << "\n" << infoLog << std::endl;
		}
	}
}

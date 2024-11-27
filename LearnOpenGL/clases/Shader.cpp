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
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILACION_FALLIDA\n" << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILACION_FALLIDA\n" << infoLog << std::endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::LINKEO_FALLIDO\n" << infoLog << std::endl;
	}

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

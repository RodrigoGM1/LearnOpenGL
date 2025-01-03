/*
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<stb_image.h>

#include<Shader.h>
#include<Camara.h>

#include<iostream>
#include<vector>
#include<map>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int cargarImagen(const char* path);
unsigned int cargarMapacubico(std::vector<std::string> faces);

Camara camara(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = 800 / 2.0f;
float lastY = 800 / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Ventana", NULL, NULL);
	if (window == NULL) {
		std::cout << "No se pudo crear la ventana GLFW" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "No se pudo inicializar GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	Shader shader("./src/4.-OpenGLAvanzado/4.8.-CubeMaps/cubo.vert", "./src/4.-OpenGLAvanzado/4.8.-CubeMaps/cubo.frag");
	Shader skyboxShader("./src/4.-OpenGLAvanzado/4.8.-CubeMaps/skybox.vert", "./src/4.-OpenGLAvanzado/4.8.-CubeMaps/skybox.frag");

	float cubeVertices[] = {
		// Back face
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
		// Front face
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
		// Left face
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
		// Right face
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
		 // Bottom face
		 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
		  0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
		  0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
		  0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
		 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
		 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
		 // Top face
		 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
		  0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
		  0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
		  0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
		 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
		 -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left
	};

	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	std::vector<std::string> faces
	{
		"./texturas/skybox/right.jpg",
		"./texturas/skybox/left.jpg",
		"./texturas/skybox/top.jpg",
		"./texturas/skybox/bottom.jpg",
		"./texturas/skybox/front.jpg",
		"./texturas/skybox/back.jpg"
	};

	//std::vector<std::string> faces
	//{
	//	"./texturas/skyboxPrueba/skybox1/1.png",
	//	"./texturas/skyboxPrueba/skybox1/2.png",
	//	"./texturas/skyboxPrueba/skybox1/3.png",
	//	"./texturas/skyboxPrueba/skybox1/4.png",
	//	"./texturas/skyboxPrueba/skybox1/5.png",
	//	"./texturas/skyboxPrueba/skybox1/6.png"
	//}

	unsigned int cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	
	unsigned int skyboxVAO, skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	unsigned int imagen = cargarImagen("./texturas/container.jpg");
	unsigned int cubemapTexture = cargarMapacubico(faces);

	shader.use();
	shader.setInt("texture1", 0);

	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	while (!glfwWindowShouldClose(window)) {
		// Entradas
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);
		// Comandos de renderizado aqui

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = camara.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camara.Zoom), (float)800 / (float)600, 0.1f, 100.0f);
		shader.setMat4("model", model);
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		glBindVertexArray(cubeVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, imagen);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glDepthFunc(GL_LEQUAL);
		skyboxShader.use();
		view = glm::mat4(glm::mat3(camara.GetViewMatrix()));
		skyboxShader.setMat4("view", view);
		skyboxShader.setMat4("projection", projection);

		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &cubeVBO);
	glDeleteBuffers(1, &skyboxVBO);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	const float	 camaraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camara.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camara.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camara.ProcessKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camara.ProcessKeyboard(RIGHT, deltaTime);
	}
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = (float)xposIn;
	float ypos = (float)yposIn;

	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camara.ProcessMouseMovement(xoffset, yoffset);

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camara.ProcessMouseScroll((float)yoffset);
}

unsigned int cargarImagen(const char* path) {
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);

	if (data) {
		GLenum format;
		if (nrComponents == 1) {
			format = GL_RED;
		}
		else if (nrComponents == 3) {
			format = GL_RGB;
		}
		else if (nrComponents == 4) {
			format = GL_RGBA;
		}

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);

		stbi_image_free(data);
	}
	else {
		std::cout << "No de pudo cargar la textura: " << path << std::endl;
		stbi_image_free(data);
	}
	return textureID;
}

unsigned int cargarMapacubico(std::vector<std::string> faces) {
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++) {
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else {
			std::cout << "No se pudo cargar el mapa cubico: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}
*/
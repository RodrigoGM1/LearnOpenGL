#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>
/*
	Se declaran los archivos de inclusión en el orden correspondiente si no arrogará un error
	1.- glad/glad
	2.- GLFW/glfw3.h
	
	Si se desea evitar el orden, se puede declarar uno #define de la siguiente manera
	1.- #define GLFW_INCLUDE_NONE
	2.- librerias
*/

// Definición de las funciones
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

int main() {
	glfwInit(); // Esta función inicia la biblioteca GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	/*
		Se puede definir como consejos o sugerencias para la creación de la ventana GLFW

		Para la creacion del contexto openGL
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	*/

	GLFWwindow* window = glfwCreateWindow(800, 600, "Ventana", NULL, NULL);// Creacion de la ventana con un tamaño de 800 x 600
	if (window == NULL) {
		std::cout << "No se pudo crear la ventana GLFW" << std::endl;
		glfwTerminate();
		return -1;
	}
	/*
		Se verifica si el ventana se creo de manera correcta en caso de que se NULL de llama la función glfwTerminate().
		La función destruye todas las ventanas y recursos restantes
	*/
	glfwMakeContextCurrent(window); // Esta función hace que el contexto OpenGL de la ventana especificada sea actual en el hilo que realizó la llamada
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Funcion establece el cambio de tamaño del buffer de marco de la ventana

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // Inicializando GLAD
		std::cout << "No se pudo inicializar GLAD" << std::endl;
		return -1;
	}


	while (!glfwWindowShouldClose(window)) { // Bucle de renderizado, el bucle de renderizado se termina hasta que la función glfwWindowShouldClose retorne un true
		// Entradas
		processInput(window);

		// Comandos de renderizado aqui

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		/*
			glClearColor(R, G, B, A) Función para especificar valores para los buffers de color
			glClear(GL_COLOR_BUFFER_BIT) Borra el buffer de color
		*/

		// Llamada de eventos y intercambio de buffers
		glfwSwapBuffers(window);
		glfwPollEvents(); // Función para el procesamiento de eventos
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height); // Establece la ventana grafica o ventana de renderizado
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true); // Bandera de cierre y cierre de ventanas
	}
	/*
		En este apartado nos permite comprobar si la tecla Esc fue precionado para poder cerrar la ventana.
	*/
}
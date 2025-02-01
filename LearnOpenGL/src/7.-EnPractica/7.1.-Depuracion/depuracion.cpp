/*
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <Shader.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void renderQuad();

GLenum glCheckError_(const char* file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "ENUM_INVALIDO"; break;
            case GL_INVALID_VALUE:                 error = "VALOR_INVALIDO"; break;
            case GL_INVALID_OPERATION:             error = "OPERACION_INVALIDA"; break;
            case GL_STACK_OVERFLOW:                error = "DESBORDAMIENTO_PILA"; break;
            case GL_STACK_UNDERFLOW:               error = "DESBORDAMIENTO_PILA"; break;
            case GL_OUT_OF_MEMORY:                 error = "SIN_MEMORIA"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALIDA_OPERACION_GRAGMENTBUFFER"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__)

void APIENTRY glDebugOutput(GLenum source,
    GLenum type,
    unsigned int id,
    GLenum severity,
    GLsizei length,
    const char* message,
    const void* userParam)
{
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return; // ignore these non-significant error codes

    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "Debug mensaje (" << id << "): " << message << std::endl;

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             std::cout << "Fuente: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Fuente: Window Sistema"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Fuente: Compilador Shader"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Fuente: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Fuente: Aplicacion"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cout << "Fuente: Otro"; break;
    } std::cout << std::endl;

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               std::cout << "Tipo: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Tipo: Comportamiento Obsoleto"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Tipo: Comportamiento Indefinido"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Tipo: Portabilidad"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Tipo: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cout << "Tipo: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Tipo: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Tipo: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cout << "Tipo: Otro"; break;
    } std::cout << std::endl;

    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Gravedad: Alta"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Gravedad: Media"; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cout << "Gravedad: Baja"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Gravedad: Notificacion"; break;
    } std::cout << std::endl;
    std::cout << std::endl;
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // makes sure errors are displayed synchronously
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    Shader shader("./src/7.-EnPractica/7.1.-Depuracion/depuracion.vert", "./src/7.-EnPractica/7.1.-Depuracion/depuracion.frag");

    unsigned int cubeVAO, cubeVBO;
    float vertices[] = {
        // back face
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, // bottom-left
        0.5f,  0.5f, -0.5f,  1.0f,  1.0f, // top-right
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f, // bottom-right         
        0.5f,  0.5f, -0.5f,  1.0f,  1.0f, // top-right
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, // bottom-left
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f, // top-left
        // front face
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, // bottom-left
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f, // bottom-right
        0.5f,  0.5f,  0.5f,  1.0f,  1.0f, // top-right
        0.5f,  0.5f,  0.5f,  1.0f,  1.0f, // top-right
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f, // top-left
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, // bottom-left
        // left face
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f, // top-right
        -0.5f,  0.5f, -0.5f, -1.0f,  1.0f, // top-left
        -0.5f, -0.5f, -0.5f, -0.0f,  1.0f, // bottom-left
        -0.5f, -0.5f, -0.5f, -0.0f,  1.0f, // bottom-left
        -0.5f, -0.5f,  0.5f, -0.0f,  0.0f, // bottom-right
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f, // top-right
        // right face
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f, // top-left
        0.5f, -0.5f, -0.5f,  0.0f,  1.0f, // bottom-right
        0.5f,  0.5f, -0.5f,  1.0f,  1.0f, // top-right         
        0.5f, -0.5f, -0.5f,  0.0f,  1.0f, // bottom-right
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f, // top-left
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, // bottom-left     
        // bottom face
        -0.5f, -0.5f, -0.5f,  0.0f,  1.0f, // top-right
        0.5f, -0.5f, -0.5f,  1.0f,  1.0f, // top-left
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f, // bottom-left
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f, // bottom-left
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, // bottom-right
        -0.5f, -0.5f, -0.5f,  0.0f,  1.0f, // top-right
        // top face
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f, // top-left
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f, // bottom-right
        0.5f,  0.5f, -0.5f,  1.0f,  1.0f, // top-right     
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f, // bottom-right
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f, // top-left
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f  // bottom-left        
    };
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int width, height, nrComponents;
    unsigned char* data = stbi_load("./texturas/wood.png", &width, &height, &nrComponents, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // set up projection matrix
    shader.use();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform1i(glGetUniformLocation(shader.ID, "tex"), 0);

    glCheckError();

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        float rotationSpeed = 10.0f;
        float angle = (float)glfwGetTime() * rotationSpeed;
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0, 0.0f, -2.5));
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 1.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

unsigned int quadVAO = 0;
unsigned int quadVBO;
void renderQuad()
{
    if (quadVAO == 0)
    {
        float quadVertices[] = {
            // positions        // texture Coords
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
*/
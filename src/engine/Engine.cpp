#include "Engine.h"

Engine::Engine(const int window_width, const int window_height) {
    // Initialize GLFW
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Imagin3D", nullptr, nullptr);
        if (window == nullptr)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(window);

    // Initialize GLAD
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            std::cerr << "Failed to initialize GLAD" << std::endl;
        }

    // Configure Viewport
        glViewport(0, 0, window_width, window_height);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    this->window = window;
}

Engine::~Engine() {
    glfwTerminate();
}

void Engine::Run() const {
    if (this->window == nullptr) std::cerr << "could not run engine: window is null" << std::endl;
    else {
        while(!glfwWindowShouldClose(this->window))
        {
            glfwSwapBuffers(this->window);
            glfwPollEvents();
        }
    }
}


void framebuffer_size_callback(GLFWwindow* window, const int width, const int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

#ifndef ENGINE_H
#define ENGINE_H
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Engine {
public:
    Engine(int window_width, int window_height);
    ~Engine();
    void Run();

private:
    GLFWwindow* window;
    void ProcessInput() const;
    void Render();
    void Triangle();
};



#endif //{}ENGINE_H

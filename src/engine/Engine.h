#ifndef ENGINE_H
#define ENGINE_H
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

class Engine {
public:
    Engine(int window_width, int window_height);
    ~Engine();
    void Run() const;

private:
    GLFWwindow* window;
};



#endif //{}ENGINE_H

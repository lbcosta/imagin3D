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
    void Run() const;

private:
    GLFWwindow* window;
    void ProcessInput() const;
    void Render() const;
};



#endif //{}ENGINE_H

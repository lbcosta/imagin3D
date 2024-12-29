#ifndef ENGINE_H
#define ENGINE_H
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <iostream>

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
    void Rectangle();
};



#endif //{}ENGINE_H

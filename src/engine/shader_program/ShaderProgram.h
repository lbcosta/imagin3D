//
// Created by lbcos on 29/12/2024.
//

#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <iostream>


class ShaderProgram {
public:
    static GLuint Create(const char* vertexSrc, const char* fragmentSrc);
};



#endif //SHADERPROGRAM_H

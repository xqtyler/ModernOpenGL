#ifndef UTILITY_H
#define UTILITY_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Utility {
    void Framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void ProcessInput(GLFWwindow* window);
    int CompileSucceed(unsigned int shaderOBj);
    int LinkSucceed(unsigned int shaderProgram);
};

namespace ShaderUtility {
    void ShaderingOrange(GLFWwindow* window);
    void ShaderingConnectedTriangle(GLFWwindow* window);
    void ShaderingUniform(GLFWwindow* window);
    void ShaderingByCustomerizedShader(GLFWwindow* window);
    void ShaderingTexture(GLFWwindow* window);
    void ShaderingTextures(GLFWwindow* window);
};

#endif


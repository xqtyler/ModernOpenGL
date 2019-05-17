#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Utility {
    void Framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void ProcessInput(GLFWwindow* window);
    int CompileSucceed(unsigned int shaderOBj);
    int LinkSucceed(unsigned int shaderProgram);
};


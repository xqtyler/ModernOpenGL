#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    // constructor reads and builds the shader
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

    // use/activate the shader
    void Use();

    // utility uniform functions
    void SetBool(const std::string &name, bool value) const;
    void SetInt(const std::string &name, int value) const;
    void SetFloat(const std::string &name, float value) const;

private:
    void CheckCompileErrors(unsigned int shader, std::string type);

private:
    // the program ID
    unsigned int m_shaderProgramId;
};

#endif
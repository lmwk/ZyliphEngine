#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <glm/glm.hpp>

std::string get_file_contents(const char* filename);

class Shader
{
public:
    GLuint ID;
    Shader(const char* vertexfile, const char* fragmentfile, const char* geomfile);
    Shader(const char* vertexfile, const char* fragmentfile);
    Shader() = default;
    Shader(const Shader&) = default;

    void Activate();
    void Delete();

    void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
private:
    void compileErrors(unsigned int shader, const char* type);
};

#endif
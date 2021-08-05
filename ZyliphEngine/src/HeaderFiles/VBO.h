#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texUv;
};

class VBO
{
public:
    GLuint ID;
    VBO(std::vector<Vertex>& vertices);
    VBO(std::vector<glm::mat4>& mat4s);

    void Bind();
    void Unbind();
    void Delete();
};

#endif
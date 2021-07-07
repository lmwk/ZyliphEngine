#ifndef ZMESH_CLASS_H
#define ZMESH_CLASS_H

#include <string>

#include "VAO.h"
#include "EBO.h"
#include "Camera.h"
#include "Texture.h"

class ZMesh
{
public:
    std::vector <Vertex> vertices;
    std::vector <GLuint> indicies;
    std::vector <Texture> textures;


    VAO VAO;

    unsigned int instances;

    ZMesh(
        std::vector <Vertex>& vertices, 
        std::vector <GLuint>& indicies, 
        std::vector <Texture>& textures,
        unsigned int instances = 1,
        std::vector<glm::mat4> instancemat4s = {}
    );
    void Draw(Shader& shader, Camera& camera, glm::mat4 matrix = glm::mat4(1.0f), glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f), glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f));
};

#endif

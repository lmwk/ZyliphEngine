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

    ZMesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indicies, std::vector <Texture>& textures);
    void Draw(Shader& shader, Camera& camera);
};

#endif

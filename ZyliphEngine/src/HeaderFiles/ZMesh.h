#ifndef ZMESH_CLASS_H
#define ZMESH_CLASS_H


#include <string>

#include "../Windowing/OpenGL/OpenGLBuffers.h"
#include "EBO.h"
#include "Camera.h"
#include "Texture.h"

namespace Zyliph
{
    class ZMesh
    {
    public:
        std::vector <Vertex> vertices;
        std::vector <GLuint> indicies;
        std::vector <Texture> textures;


        VertexArrayBuffer* VAO;
        Ref<IndexBuffer> EBO;

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
}

#endif

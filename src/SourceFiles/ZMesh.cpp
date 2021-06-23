﻿#include "../HeaderFiles/ZMesh.h"

ZMesh::ZMesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indicies, std::vector<Texture>& textures)
{
    ZMesh::vertices = vertices;
    ZMesh::indicies = indicies;
    ZMesh::textures = textures;

    VAO.Bind();

    VBO VBO(vertices);
    EBO EBO(indicies);

    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), static_cast<void*>(0));
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), reinterpret_cast<void*>(3 * sizeof(float)));
    VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), reinterpret_cast<void*>(6 * sizeof(float)));
    VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), reinterpret_cast<void*>(9 * sizeof(float)));
    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();
}

void ZMesh::Draw(Shader& shader, Camera& camera)
{
    shader.Activate();
    VAO.Bind();

    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        std::string num;
        std::string type = textures[i].type;
        if (type == "diffuse")
        {
            num = std::to_string(numDiffuse++);
        }
        else if (type == "specular")
        {
            num = std::to_string(numSpecular++);
        }
        textures[i].texUnit(shader, (type + num).c_str(), i);
        textures[i].Bind();
    }
    glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
    camera.Matrix(shader, "camMatrix");

    glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
}

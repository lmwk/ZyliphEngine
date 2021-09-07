#include "../HeaderFiles/ZMesh.h"

#include "../Rendering/RenderCommand.h"

namespace Zyliph
{
    ZMesh::ZMesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indicies, std::vector<Texture>& textures, unsigned instances, std::vector<glm::mat4> instancemat4s)
    {
        ZMesh::vertices = vertices;
        ZMesh::indicies = indicies;
        ZMesh::textures = textures;
        ZMesh::instances = instances;

        VAO = VertexArrayBuffer::Create();
        VAO->Bind();

        VertexBuffer* instanceVBO = VertexBuffer::Create(instancemat4s);
        VertexBuffer* VBO = VertexBuffer::Create(vertices);
        EBO.reset(IndexBuffer::Create(indicies));

        VAO->LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), 0);
        VAO->LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), reinterpret_cast<void*>(3 * sizeof(float)));
        VAO->LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), reinterpret_cast<void*>(6 * sizeof(float)));
        VAO->LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), reinterpret_cast<void*>(9 * sizeof(float)));
        if (instances != 1)
        {
            instanceVBO->Bind();

            VAO->LinkAttrib(instanceVBO, 4, 4, GL_FLOAT, sizeof(glm::mat4), (void*)0);
            VAO->LinkAttrib(instanceVBO, 5, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(1 * sizeof(glm::vec4)));
            VAO->LinkAttrib(instanceVBO, 6, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
            VAO->LinkAttrib(instanceVBO, 7, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

            glVertexAttribDivisor(4, 1);
            glVertexAttribDivisor(5, 1);
            glVertexAttribDivisor(6, 1);
            glVertexAttribDivisor(7, 1);
        }

        VAO->UnBind();
        VBO->UnBind();
        instanceVBO->UnBind();
        EBO->UnBind();
    }

    void ZMesh::Draw(Shader& shader, Camera& camera, glm::mat4 matrix, glm::vec3 translation, glm::quat rotation, glm::vec3 scale)
    {
        shader.Activate();
        VAO->Bind();

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

        if (instances == 1)
        {

            glm::mat4 trans = glm::mat4(1.0f);
            glm::mat4 rot = glm::mat4(1.0f);
            glm::mat4 sca = glm::mat4(1.0f);

            trans = glm::translate(trans, translation);
            rot = glm::mat4_cast(rotation);
            sca = glm::scale(sca, scale);

            glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
            glUniformMatrix4fv(glGetUniformLocation(shader.ID, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
            glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, glm::value_ptr(sca));
            glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));

            RenderCommand::DrawIndexed(EBO);
        }
        else
        {
            glDrawElementsInstanced(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0, instances);
        }
    }

}
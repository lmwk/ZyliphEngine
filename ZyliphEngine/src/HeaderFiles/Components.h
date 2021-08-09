#pragma once
#include "ZModel.h"

namespace Zyliph
{
    struct IdentifierComponent
    {
        std::string name;

        IdentifierComponent() = default;
        IdentifierComponent(const IdentifierComponent&) = default;
    };

    struct MeshRendererComponent
    {
        ZModel Model;
        Shader shader;
        Camera cam;

        MeshRendererComponent(std::string filepath, Shader _shader, Camera _cam)
        {
            Model = ZModel{filepath.c_str(), 1};
            shader = _shader;
            cam = _cam;
        }
        MeshRendererComponent(const MeshRendererComponent&) = default;

        void draw(glm::vec3 translation, glm::quat rotation, glm::vec3 scale)
        {
            Model.Draw(shader, cam, translation, rotation, scale);
        }
    };

    struct TransformComponent
    {
        glm::vec3 translation = glm::vec3(0, 0, 0);
        glm::quat rotation = glm::quat(1, 0, 0, 0);
        glm::vec3 scale = glm::vec3(1, 1, 1);

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
    };
}
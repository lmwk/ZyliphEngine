#pragma once

#include <glm/glm.hpp>

namespace Zyliph
{
    class OrthoCamera
    {
    public:
        OrthoCamera(float left, float right, float bottom, float top);

        const glm::vec3& GetPosition() const { return z_Position; }
        void SetPosition(const glm::vec3& position) { z_Position = position; RecalculateViewMatrix();}

        float GetRotation() const { return z_Rotation; }
        void SetRotation(float rotation) { z_Rotation = rotation; RecalculateViewMatrix();}

        const glm::mat4& GetProjectionMatrix() const { return z_ProjectionMatrix; }
        const glm::mat4& GetViewMatrix() const { return z_ViewMatrix; }
        const glm::mat4& GetViewProjMatrix() const { return z_ViewProjectionMatrix; }
    private:
        void RecalculateViewMatrix();
    private:
        glm::mat4 z_ProjectionMatrix;
        glm::mat4 z_ViewMatrix;
        glm::mat4 z_ViewProjectionMatrix;

        glm::vec3 z_Position = {0.0f, 0.0f, 0.0f};
        float z_Rotation = 0.0f;
    };
}

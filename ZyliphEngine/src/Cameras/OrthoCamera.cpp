#include "OrthoCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Zyliph
{
    OrthoCamera::OrthoCamera(float left, float right, float bottom, float top)
        :z_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, -1.0f)), z_ViewMatrix(1.0f)
    {
        z_ViewProjectionMatrix = z_ProjectionMatrix * z_ViewMatrix;
    }

    void OrthoCamera::RecalculateViewMatrix()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), z_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(z_Rotation), glm::vec3(0, 0, 1));

        z_ViewMatrix = glm::inverse(transform);
        z_ViewProjectionMatrix = z_ProjectionMatrix * z_ViewMatrix;
    }
}

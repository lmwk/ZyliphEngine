#include "../HeaderFiles/Camera.h"

#include "../Utils/KeyCodes.h"

namespace Zyliph
{
    Camera::Camera(int width, int height, glm::vec3 position)
    {
        Camera::width = width;
        Camera::height = height;
        Position = position;
    }

    void Camera::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane)
    {
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        view = glm::lookAt(Position, Position + Orientation, Up);
        projection = glm::perspective(glm::radians(FOVdeg), static_cast<float>(width) / height, nearPlane, farPlane);

        cameraMatrix = projection * view;
    }

    void Camera::Matrix(Shader& shader, const char* uniform)
    {
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
    }


    void Camera::KeyInputs(double deltatime)
    {


        if (Input::IsKeyPressed(W))
        {
            Position += speed * Orientation * static_cast<float>(deltatime / 10);
        }
        if (Input::IsKeyPressed(A))
        {
            Position += speed * -glm::normalize(glm::cross(Orientation, Up)) * static_cast<float>(deltatime / 10);
        }
        if (Input::IsKeyPressed(S))
        {
            Position += speed * -Orientation * static_cast<float>(deltatime / 10);
        }
        if (Input::IsKeyPressed(D))
        {
            Position += speed * glm::normalize(glm::cross(Orientation, Up)) * static_cast<float>(deltatime / 10);
        }

        if (Input::IsKeyPressed(SPACE))
        {
            Position += speed * Up;
        }
        if (Input::IsKeyPressed(LEFT_CONTROL))
        {
            Position += speed * -Up;
        }
        if (Input::IsKeyPressed(LEFT_SHIFT))
        {
            speed = 10.0f;
        }
        else if (Input::IsKeyPressed(LEFT_SHIFT) == false)
        {
            speed = 7.8f;
        }
        if (Input::IsMouseButtonPressed(MOUSE_LEFT))
        {
            Input::SetInputMode(CURSOR, CURSOR_HIDDEN);

            if (firstclick)
            {
                Input::SetMousePos((width / 2), (height / 2));
                firstclick = false;
            }

            glm::vec2 pos = Input::GetMousePos();
            double mouseX = pos.x;
            double mouseY = pos.y;

            float rotX = sensitivity * static_cast<float>(mouseY - (height / 2)) / height;
            float rotY = sensitivity * static_cast<float>(mouseX - (width / 2)) / width;

            glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

            if (!((glm::angle(newOrientation, Up) <= glm::radians(5.0f))) || (glm::angle(newOrientation, -Up) <= glm::radians(5.0f)))
            {
                Orientation = newOrientation;
            }

            Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

            Input::SetMousePos((width / 2), (height / 2));

        }
        else if (Input::IsMouseButtonPressed(MOUSE_LEFT))
        {
            Input::SetInputMode(CURSOR, CURSOR_NORMAL);
            firstclick = true;
        }

    }

    void Camera::GamePadInputs(double deltatime)
    {
        if (joystick1Present == 1)
        {
            Input::SetInputMode(CURSOR, CURSOR_NORMAL);
            const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
            const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
            Input::SetMousePos((width / 2), (height / 2));
            if (axes[3] <= -0.3f || axes[3] >= 0.3f || axes[2] <= -0.3f || axes[2] >= 0.3f)
            {
                float rotX = 0.0f;
                float rotY = 0.0f;
                glm::vec2 pos = Input::GetMousePos();

                double mouseX = pos.x;
                double mouseY = pos.y;

                rotX = (static_cast<float>(mouseY) + sensitivity * axes[3] * static_cast<float>(deltatime / 10) - (height / 2)) / 2;
                rotY = (static_cast<float>(mouseX) + sensitivity * axes[2] * static_cast<float>(deltatime / 10) - (width / 2)) / 2;

                const glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

                if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
                {
                    Orientation = newOrientation;
                }

                Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

                Input::SetMousePos((width / 2), (height / 2));
            }

            if (axes[1] >= 0.2f)
            {
                Position += speed * -Orientation * axes[1] * static_cast<float>(deltatime / 10);
            }
            if (axes[1] <= -0.2f)
            {
                Position += speed * -Orientation * axes[1] * static_cast<float>(deltatime / 10);
            }
            if (axes[0] >= 0.3f)
            {
                Position += speed * glm::normalize(glm::cross(Orientation, Up)) * axes[0] * static_cast<float>(deltatime / 10);
            }
            //Fixed, but a bit slow
            if (axes[0] <= -0.3f)
            {
                Position += speed * glm::normalize(glm::cross(Orientation, Up)) * axes[0] * static_cast<float>(deltatime / 10);
            }

            if (GLFW_PRESS == buttons[0])
            {
                Position += speed * Up * static_cast<float>(deltatime / 10);
            }

            if (GLFW_PRESS == buttons[1])
            {
                Position += speed * -Up * static_cast<float>(deltatime / 10);
            }

        }
    }

}
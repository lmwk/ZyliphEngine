#include "../HeaderFiles/Camera.h"



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


void Camera::KeyInputs(GLFWwindow* window, double deltatime)
{


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        Position += speed * Orientation * static_cast<float>(deltatime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        Position += speed * -glm::normalize(glm::cross(Orientation, Up)) * static_cast<float>(deltatime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        Position += speed * -Orientation * static_cast<float>(deltatime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        Position += speed * glm::normalize(glm::cross(Orientation, Up)) * static_cast<float>(deltatime);
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        Position += speed * Up;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        Position += speed * -Up;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        speed = 0.4f;
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)
    {
        speed = 0.1f;
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if (firstclick)
        {
            glfwSetCursorPos(window, (width / 2), (height / 2));
            firstclick = false;
        }

        double mouseX;
        double mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float rotX = sensitivity * static_cast<float>(mouseY - (height / 2)) / height;
        float rotY = sensitivity * static_cast<float>(mouseX - (width / 2)) / width;

        glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

        if (!((glm::angle(newOrientation, Up) <= glm::radians(5.0f))) or (glm::angle(newOrientation, -Up) <= glm::radians(5.0f)))
        {
            Orientation = newOrientation;
        }

        Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

        glfwSetCursorPos(window, (width / 2), (height / 2));

    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstclick = true;
    }

}

void Camera::GamePadInputs(GLFWwindow* window, double deltatime)
{
    if (joystick1Present == 1)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
        const unsigned char *buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
        glfwSetCursorPos(window, (width / 2), (height / 2));
        if (axes[3] <= -0.3f or axes[3] >= 0.3f or axes[2] <= -0.3f or axes[2] >= 0.3f)
        {

            double mouseX;
            double mouseY;

            float rotX = 0.0f;
            float rotY = 0.0f;
            glfwGetCursorPos(window, &mouseX, &mouseY);

            rotX = (static_cast<float>(mouseY) + sensitivity * axes[3] * static_cast<float>(deltatime) - (height / 2)) / 2;
            rotY = (static_cast<float>(mouseX) + sensitivity * axes[2] * static_cast<float>(deltatime) - (width / 2)) / 2;

            const glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

            if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
            {
                Orientation = newOrientation;
            }

            Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

            glfwSetCursorPos(window, (width / 2), (height / 2));
        }

        if (axes[1] >= 0.2f)
        {
            Position += speed * -Orientation * axes[1] * static_cast<float>(deltatime);
        }
        if (axes[1] <= -0.2f)
        {
            Position += speed * -Orientation * axes[1] * static_cast<float>(deltatime);
        }
        if (axes[0] >= 0.3f)
        {
            Position += speed * glm::normalize(glm::cross(Orientation, Up)) * axes[0] * static_cast<float>(deltatime);
        }
        //Fixed, but a bit slow
        if (axes[0] <= -0.3f)
        {
            Position += speed * glm::normalize(glm::cross(Orientation, Up)) * axes[0] * static_cast<float>(deltatime);
        }

        if (GLFW_PRESS == buttons[0])
        {
            Position += speed * Up * static_cast<float>(deltatime);
        }

        if (GLFW_PRESS == buttons[1])
        {
            Position += speed * -Up * static_cast<float>(deltatime);
        }

    }
}

#include "WindowsInput.h"

#include "../../../Testing/Test.h"
#include <GLFW/glfw3.h>

namespace Zyliph
{

    Input* Input::z_Instance = new WindowsInput();

    bool WindowsInput::IsKeyPressedImpl(int keycode)
    {
        auto window = static_cast<GLFWwindow*>(TestApp::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::IsMouseButtonPressedImpl(int button)
    {
        auto window = static_cast<GLFWwindow*>(TestApp::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    float WindowsInput::GetMouseXImpl()
    {
        auto pos = GetMousePosImpl();

        return pos.x;
    }

    float WindowsInput::GetMouseYImpl()
    {
        auto pos = GetMousePosImpl();

        return pos.y;
    }
    glm::vec2 WindowsInput::GetMousePosImpl()
    {
        auto window = static_cast<GLFWwindow*>(TestApp::Get().GetWindow().GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        return glm::vec2(xpos, ypos);
    }

    void WindowsInput::SetMousePosImpl(double xpos, double ypos)
    {
        auto window = static_cast<GLFWwindow*>(TestApp::Get().GetWindow().GetNativeWindow());
        glfwSetCursorPos(window, xpos, ypos);
    }

    void WindowsInput::SetInputModeImpl(int inputmode, int visibility)
    {
        auto window = static_cast<GLFWwindow*>(TestApp::Get().GetWindow().GetNativeWindow());
        glfwSetInputMode(window,inputmode, visibility);
    }


}

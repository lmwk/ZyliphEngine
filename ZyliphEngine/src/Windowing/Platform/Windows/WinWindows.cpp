#include "WinWindows.h"

namespace Zyliph
{
    static bool IsGlfwInit = false;

    static void GLFWErrorCallback(int error, const char* desc)
    {
        Z_CORE_ERROR("GLFW Error ({0}): {1}", error, desc);
    }

    Scope<Window> Window::Create(const WindowVals& vals)
    {
        return CreateScope<WinWindow>(vals);
    }

    WinWindow::WinWindow(const WindowVals& vals)
    {
        Init(vals);
    }

    WinWindow::~WinWindow()
    {
        Shutdown();
    }

    void WinWindow::Init(const WindowVals& vals)
    {
        z_Data.title = vals.Title;
        z_Data.Width = vals.width;
        z_Data.Height = vals.height;

        Z_CORE_INFO("Creating window {0} ({1}, {2})", vals.Title, vals.width, vals.height);

        if (!IsGlfwInit)
        {
            int success = glfwInit();
            Z_CORE_ASSERT(success, "Could not Initialize GLFW");

            glfwSetErrorCallback(GLFWErrorCallback);

            IsGlfwInit = true;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        z_Window = glfwCreateWindow(static_cast<int>(vals.width), static_cast<int>(vals.height), z_Data.title.c_str(),
                                    nullptr, nullptr);
        glfwMakeContextCurrent(z_Window);
        glfwSetWindowUserPointer(z_Window, &z_Data);
        SetVSync(true);

        glfwSetWindowSizeCallback(z_Window, [](GLFWwindow* window, int width, int height)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
                data.Width = width;
                data.Height = height;

                WindowResizeEvent event(width, height);

                data.EventCallback(event);
            });

        glfwSetWindowCloseCallback(z_Window, [](GLFWwindow* window)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
                WindowCloseEvent event;
                data.EventCallback(event);
            });

        glfwSetKeyCallback(z_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

                switch (action)
                {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
                }

            });

        glfwSetCharCallback(z_Window, [](GLFWwindow* window, unsigned int character)
        {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

                KeyTypedEvent event(character);
                data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(z_Window, [](GLFWwindow* window, int button, int action, int mods)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

                switch (action)
                {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                }
            });

        glfwSetScrollCallback(z_Window, [](GLFWwindow* window, double xOffset, double yOffset)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

                MouseScrolledEvent event((float)xOffset, (float)yOffset);
                data.EventCallback(event);
            });

        glfwSetCursorPosCallback(z_Window, [](GLFWwindow* window, double xPos, double yPos)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

                MouseMovedEvent event((float)xPos, (float)yPos);
                data.EventCallback(event);
            });

        gladLoadGL();
    }

    void WinWindow::Shutdown()
    {
        glfwDestroyWindow(z_Window);
    }

    void WinWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(z_Window);
    }

    void WinWindow::SetVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        z_Data.Vsync = enabled;
    }

    bool WinWindow::IsVSync() const
    {
        return z_Data.Vsync;
    }
}

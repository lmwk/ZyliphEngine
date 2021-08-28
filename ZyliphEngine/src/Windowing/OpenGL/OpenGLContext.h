#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../../Rendering/GraphicsContext.h"

namespace Zyliph
{
    class OpenGLContext : public GraphicsContext
    {
    public:

        OpenGLContext(GLFWwindow* windowH);
        void Init() override;
        void SwapBuffers() override;
    private:
        GLFWwindow* z_windowH;
    };
}
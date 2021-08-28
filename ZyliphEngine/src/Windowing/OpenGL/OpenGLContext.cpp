#include "OpenGLContext.h"

#include "../../Core/Assert.h"

namespace Zyliph
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowH) : z_windowH(windowH)
    {
        Z_CORE_ASSERT(windowH, "Window Handle is null");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(z_windowH);
        int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        Z_CORE_ASSERT(status, "Failed to init Glad");
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(z_windowH);
    }
}

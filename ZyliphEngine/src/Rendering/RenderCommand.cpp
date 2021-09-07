#include "RenderCommand.h"

#include "../Windowing/OpenGL/OpenGLRendererAPI.h"

namespace Zyliph
{
#if defined(Z_PLATFORM_WINDOWS)
    RendererAPI* RenderCommand::z_RendererAPI = new OpenGLRendererAPI;
#else
    
#endif
}
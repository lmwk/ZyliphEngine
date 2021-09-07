#include "RendererAPI.h"
#include "../Core/Core.h"

namespace Zyliph
{
#if defined(Z_PLATFORM_WINDOWS)
    RendererAPI::API RendererAPI::z_API = RendererAPI::API::OpenGL;
#else
    RendererAPI::API RendererAPI::z_API = RendererAPI::API::None;
#endif
}
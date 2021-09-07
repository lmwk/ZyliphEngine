#pragma once

#include <glm/glm.hpp>
#include "../Buffers/Buffer.h"
#include "../Core/Core.h"

namespace Zyliph
{
    class RendererAPI
    {
    public:
        enum class API
        {
            None = 0, OpenGL = 2
        };
    public:
        virtual void SetClearColor(const glm::vec4 color) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(const Ref<IndexBuffer>& indxbuffer) = 0;

        inline static  API GetAPI() { return z_API; }
    private:
        static API z_API;
    };
}

#pragma once

#include "RendererAPI.h"

namespace Zyliph
{
    class RenderCommand
    {
    public:

        inline static void SetClearColor(const glm::vec4& color)
        {
            z_RendererAPI->SetClearColor(color);
        }

        inline static void Clear()
        {
            z_RendererAPI->Clear();
        }
        inline static  void DrawIndexed(const Ref<IndexBuffer>& indxbuffer)
        {
            z_RendererAPI->DrawIndexed(indxbuffer);
        }
    private:
        static RendererAPI* z_RendererAPI;
    };
}

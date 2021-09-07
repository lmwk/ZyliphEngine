#pragma once

#include "../../Rendering/RendererAPI.h"

namespace Zyliph
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        void SetClearColor(const glm::vec4 color) override;
        void Clear() override;

        void DrawIndexed(const Ref<IndexBuffer>& indxbuffer) override;
    };
}
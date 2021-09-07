#pragma once

#include "RenderCommand.h"

#include "../Cameras/OrthoCamera.h"
#include "../HeaderFiles/shaderClass.h"

namespace Zyliph
{

    class Renderer
    {
    public:
        static void BeginScene(OrthoCamera& cam);
        static void EndScene();

        static void Submit(const Ref<IndexBuffer>& inxbf, const Ref<Shader>& shader);

        static RendererAPI::API GetApi() { return RendererAPI::GetAPI(); }
    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

        static Scope<SceneData> z_SceneData;
    };

}

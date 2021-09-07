#include "Renderer.h"

namespace Zyliph
{
    Scope<Renderer::SceneData> Renderer::z_SceneData = CreateScope<Renderer::SceneData>();

    void Renderer::BeginScene(OrthoCamera& cam)
    {
        z_SceneData->ViewProjectionMatrix = cam.GetViewProjMatrix();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const Ref<IndexBuffer>& inxbf, const Ref<Shader>& shader)
    {
        shader->Activate();
        shader->UploadUniformMat4("z_ViewProj", z_SceneData->ViewProjectionMatrix);

        inxbf->Bind();
        RenderCommand::DrawIndexed(inxbf);
    }
}

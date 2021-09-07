#include "Buffer.h"

#include "../Rendering/Renderer.h"
#include "../Core/Assert.h"
#include "../Windowing/OpenGL/OpenGLBuffers.h"
namespace Zyliph
{
    VertexBuffer* VertexBuffer::Create(std::vector<Vertex>& vertices)
    {
        switch (Renderer::GetApi())
        {
        case RendererAPI::API::None:
            Z_CORE_ASSERT(false, "No found supported Rendering API");
            break;

        case RendererAPI::API::OpenGL:
            return new OpenGLVertexBuffer(vertices);
        }
    }

    VertexBuffer* VertexBuffer::Create(std::vector<glm::mat4>& mat4s)
    {
        switch (Renderer::GetApi())
        {
        case RendererAPI::API::None:
            Z_CORE_ASSERT(false, "No found supported Rendering API");
            break;

        case RendererAPI::API::OpenGL:
            return new OpenGLVertexBuffer(mat4s);
        }

        Z_CORE_ASSERT(false, "Unknown Rendering APi");
        return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(std::vector<unsigned>& indicies)
    {
        switch (Renderer::GetApi())
        {
        case RendererAPI::API::None:
            Z_CORE_ASSERT(false, "No found supported Rendering API");
            break;

        case RendererAPI::API::OpenGL:
            return new OpenGLIndexBuffer(indicies);
        }

        Z_CORE_ASSERT(false, "Unknown Rendering APi");
        return nullptr;
    }

    VertexArrayBuffer* VertexArrayBuffer::Create()
    {
        switch (Renderer::GetApi())
        {
        case RendererAPI::API::None:
            Z_CORE_ASSERT(false, "No found supported Rendering API");
            break;

        case RendererAPI::API::OpenGL:
            return new OpenGLVertexArrayBuffer();
        }

        Z_CORE_ASSERT(false, "Unknown Rendering APi");
        return nullptr;
    }


}
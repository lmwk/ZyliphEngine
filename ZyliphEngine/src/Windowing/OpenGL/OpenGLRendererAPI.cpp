#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

void Zyliph::OpenGLRendererAPI::SetClearColor(const glm::vec4 color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void Zyliph::OpenGLRendererAPI::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Zyliph::OpenGLRendererAPI::DrawIndexed(const Ref<IndexBuffer>& indxbuffer)
{
    indxbuffer->Bind();
    glDrawElements(GL_TRIANGLES, indxbuffer->indiciesArray.size(), GL_UNSIGNED_INT, nullptr);
}

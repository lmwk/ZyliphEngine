#include "OpenGLBuffers.h"

namespace Zyliph
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(std::vector<Vertex>& vertices)
    {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(std::vector<glm::mat4>& mat4s)
    {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER, mat4s.size() * sizeof(glm::mat4), mat4s.data(), GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &ID);
    }

    void OpenGLVertexBuffer::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, ID);
    }

    void OpenGLVertexBuffer::UnBind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    OpenGLIndexBuffer::OpenGLIndexBuffer(std::vector<unsigned>& indicies)
    {
        indiciesArray = indicies;

        glGenBuffers(1, &ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(GLuint), indicies.data(), GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &ID);
    }

    void OpenGLIndexBuffer::Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    }

    void OpenGLIndexBuffer::UnBind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    OpenGLVertexArrayBuffer::OpenGLVertexArrayBuffer()
    {
        glGenVertexArrays(1, &ID);
    }

    OpenGLVertexArrayBuffer::~OpenGLVertexArrayBuffer()
    {
        glDeleteVertexArrays(1, &ID);
    }

    void OpenGLVertexArrayBuffer::Bind()
    {
        glBindVertexArray(ID);
    }

    void OpenGLVertexArrayBuffer::UnBind()
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArrayBuffer::LinkAttrib(VertexBuffer* VBO, unsigned layout, unsigned numcomponents, unsigned type,
        long long stride, void* offset)
    {
        VBO->Bind();
        glVertexAttribPointer(layout, numcomponents, type, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(layout);
        VBO->UnBind();
    }
}

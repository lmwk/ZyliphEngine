#pragma once

#include <glad/glad.h>
#include "../../Buffers/Buffer.h"

namespace Zyliph
{

    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        unsigned int ID;
        OpenGLVertexBuffer(std::vector<Vertex>& vertices);
        OpenGLVertexBuffer(std::vector<glm::mat4>& mat4s);
        virtual ~OpenGLVertexBuffer();

        void Bind() override;
        void UnBind() override;
        
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        unsigned int ID;
        OpenGLIndexBuffer(std::vector<unsigned>& indicies);
        virtual ~OpenGLIndexBuffer();

        void Bind() override;
        void UnBind() override;
    };

    class OpenGLVertexArrayBuffer : public VertexArrayBuffer
    {
    public:
        unsigned int ID;
        OpenGLVertexArrayBuffer();
        virtual ~OpenGLVertexArrayBuffer();

        void Bind() override;
        void UnBind() override;
        void LinkAttrib(VertexBuffer* VBO, unsigned layout, unsigned numcomponents, unsigned type, long long stride, void* offset) override;
    };

}
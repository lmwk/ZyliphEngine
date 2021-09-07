#pragma once
#include <vector>
#include <glm/glm.hpp>

namespace Zyliph
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 color;
        glm::vec2 texUv;
    };

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}

        virtual void Bind() = 0;
        virtual void UnBind() = 0;

        static VertexBuffer* Create(std::vector<Vertex>& vertices);
        static VertexBuffer* Create(std::vector<glm::mat4>& mat4s);
    };

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() {}

        virtual void Bind() = 0;
        virtual void UnBind() = 0;

        std::vector<unsigned int> indiciesArray;

        static IndexBuffer* Create(std::vector<unsigned int>& indicies);
    };

    class VertexArrayBuffer
    {
    public:
        virtual ~VertexArrayBuffer() {}

        virtual void Bind() = 0;
        virtual void UnBind() = 0;
        virtual void LinkAttrib(VertexBuffer* VBO, unsigned int layout, unsigned int numcomponents, unsigned int type, signed long long int stride, void* offset) = 0;

        static VertexArrayBuffer* Create();
    };
}

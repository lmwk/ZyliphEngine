#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <json/json.h>
#include "ZMesh.h"

using json = nlohmann::json;

namespace Zyliph
{
    class ZModel
    {
    public:
        ZModel(const char* file, unsigned int instances, std::vector<glm::mat4> instancemat4s = {});
        ZModel() = default;
        ZModel(const ZModel&) = default;

        void Draw
        (
            Shader& shader,
            Camera& camera,
            glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
            glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
            glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
        );

    private:
        const char* file;
        std::vector<unsigned char> data;
        json JSON;
        unsigned int instances;

        std::vector<ZMesh> meshes;
        std::vector<glm::vec3> translationMeshes;
        std::vector<glm::quat> rotationMeshes;
        std::vector<glm::vec3> scalesMeshes;
        std::vector<glm::mat4> matricesMeshes;
        std::vector<glm::mat4> instancemat4s;

        std::vector<std::string> loadedTexNames;
        std::vector<Texture> loadedTextures;

        void loadMesh(unsigned int indMesh);

        void TraverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

        std::vector<unsigned char> getData();
        std::vector<float> getFloats(json accessor);
        std::vector<GLuint> getIndices(json accessor);
        std::vector<Texture> getTextures();

        std::vector<Vertex> assembleVertices
        (
            std::vector<glm::vec3> positions,
            std::vector<glm::vec3> normals,
            std::vector<glm::vec2> texUVs
        );

        std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
        std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
        std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);
    };
}


#endif

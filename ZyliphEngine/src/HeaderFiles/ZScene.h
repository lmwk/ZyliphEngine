#ifndef ZSCENE_CLASS_H
#define ZSCENE_CLASS_H
#include <memory>
#include <map>
#include <entt/entt.hpp>

#include "ZPostProcessingBuffer.h"
#include "../HeaderFiles/Camera.h"
#include "../HeaderFiles/shaderClass.h"

class ZEntity;

class ZScene
{
public:
    ZScene() : zCamera(nullptr), zPostProcessing(nullptr), zBaseShader(nullptr), zSize(800, 600), zManager(nullptr)
    {
        zPostProcessing = std::make_unique<ZPostProcessingBuffer>();
        zBaseShader = std::make_unique<Shader>("fill eventually", "fill eventually");
        zCamera = std::make_unique<Camera>(zSize.x, zSize.y, glm::vec3(0.0f, 0.0f, 2.0f));
        zManager = std::make_unique<entt::registry>();
    }

    ~ZScene()
    {
        zBaseShader->Delete();
        zPostProcessing->DeleteBuffers();
    }

    std::unique_ptr<entt::registry> zManager;

    void resize_sceneView(int width, int height);

    void render(double deltatime);
    ZEntity create_entity(std::string name);

    void reset_cam() { zCamera->Position = glm::vec3(0.0f, 0.0f, 2.0f); }

private:
    std::unique_ptr<Camera> zCamera;
    std::unique_ptr<ZPostProcessingBuffer> zPostProcessing;
    std::unique_ptr<Shader> zBaseShader;
    glm::vec2 zSize;
};

#endif


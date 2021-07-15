#ifndef ZSCENE_CLASS_H
#define ZSCENE_CLASS_H
#include <memory>
#include <map>

#include "../HeaderFiles/Camera.h"
#include "../HeaderFiles/shaderClass.h"
#include "../HeaderFiles/Light.h"
#include "../HeaderFiles/ECS.h"

class ZScene
{
public:
    ZScene() : zCamera(nullptr), zPostProcessing(nullptr), zBaseShader(nullptr), zSize(800, 600)
    {
        zPostProcessing = std::make_unique<ZPostProcessingBuffer>();
        zBaseShader = std::make_unique<Shader>("fill eventually", "fill eventually");
        zCamera = std::make_unique<Camera>(zSize.x, zSize.y, glm::vec3(0.0f, 0.0f, 2.0f));
    }

    ~ZScene()
    {
        zBaseShader->Delete();
    }

    std::shared_ptr<Entity> get_entity(std::string name);

    void resize_sceneView(int width, int height);

    void render();

    Entity create_entity(std::string name);

    void reset_cam() { zCamera->Position = glm::vec3(0.0f, 0.0f, 2.0f); }

private:
    Manager zManager;
    std::unique_ptr<Camera> zCamera;
    std::unique_ptr<ZPostProcessingBuffer> zPostProcessing;
    std::unique_ptr<Shader> zBaseShader;
    glm::vec2 zSize;
};

#endif
#ifndef ZSCENE_CLASS_H
#define ZSCENE_CLASS_H
#include <memory>
#include <map>

#include "../HeaderFiles/Camera.h"
#include "../HeaderFiles/shaderClass.h"
#include "../HeaderFiles/Light.h"
#include "../HeaderFiles/ZObject.h"

class ZScene
{
public:
    ZScene() : zCamera(nullptr), zPostProcessing(nullptr), zBaseShader(nullptr), zLights(nullptr), zSize(800, 600)
    {
        zPostProcessing = std::make_unique<ZPostProcessingBuffer>();
        zBaseShader = std::make_unique<Shader>("fill eventually", "fill eventually");
        zLights = std::make_unique<std::map<std::string, ZLight>>();
        zCamera = std::make_unique<Camera>(zSize.x, zSize.y, glm::vec3(0.0f, 0.0f, 2.0f));
    }

    ~ZScene()
    {
        zBaseShader->Delete();
    }

    ZLight get_light(std::string name);

    ZObject get_object(std::string name);

    void resize_sceneView(int width, int height);

    void render();

    void add_object(std::string name, ZObject object);
    
private:
    std::unique_ptr<Camera> zCamera;
    std::unique_ptr<ZPostProcessingBuffer> zPostProcessing;
    std::unique_ptr<Shader> zBaseShader;
    std::unique_ptr<std::map<std::string,ZLight>> zLights;
    std::unique_ptr<std::map<std::string,ZObject>> zObjects;
    glm::vec2 zSize;
};

#endif
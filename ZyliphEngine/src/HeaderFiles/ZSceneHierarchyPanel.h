#ifndef ZSCENEHIERARCHYPANEL_CLASS_H
#define ZSCENEHIERARCHYPANEL_CLASS_H
#include "ZScene.h"
#include "ZEntity.h"
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

class ZSceneHierarchyPanel
{
public:

    ZSceneHierarchyPanel(const std::shared_ptr<ZScene>& scene);

    void SetSceneCtx(const std::shared_ptr<ZScene>& scene);

    void render();

private:

    void DrawEntityNode(std::unique_ptr<ZEntity>& entity);

    std::shared_ptr<ZScene> SceneRef;
    ZEntity zSelectionContext;
};

#endif
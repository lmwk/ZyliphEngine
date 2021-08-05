#include "../HeaderFiles/ZSceneHierarchyPanel.h"

ZSceneHierarchyPanel::ZSceneHierarchyPanel(const std::shared_ptr<ZScene>& scene)
{
    SetSceneCtx(scene);
}

void ZSceneHierarchyPanel::SetSceneCtx(const std::shared_ptr<ZScene>& scene)
{
    SceneRef = scene;
}

void ZSceneHierarchyPanel::render()
{
    ImGui::Begin("Scene Hierarchy");

    ImGui::End();
}



void ZSceneHierarchyPanel::DrawEntityNode(std::unique_ptr<ZEntity>& entity)
{

    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_Selected;

    
}

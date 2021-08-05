#include "../HeaderFiles/ZPropertyPanel.h"

void ZPropertyPanel::render(ZScene zScene)
{
    auto entities = &zScene.zManager;

    ImGui::Begin("Properties");
    if (ImGui::CollapsingHeader("Entity", ImGuiTreeNodeFlags_DefaultOpen))
    {
        
    }
}

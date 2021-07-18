#ifndef ZPROPERTYPANEL_CLASS_H
#define  ZPROPERTYPANEL_CLASS_H

#include "ZScene.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/ImFileBrowser/ImFileBrowser.h>

class ZPropertyPanel
{
public:

    ZPropertyPanel()
    {
        zCurrentScene = "< ... >";

        zFileDialog.SetTitle("Add model");
        zFileDialog.SetFileFilters({ ".gltf" });
    }

    void render(ZScene zScene);

    void SetMeshLoadCallback(std::function<void(const std::string&)> callback)
    {
        zMeshLoadCallback = callback;
    }

private:
    ImGui::FileBrowser zFileDialog;

    std::function<void(const std::string&)> zMeshLoadCallback;

    std::string zCurrentScene;
};

#endif
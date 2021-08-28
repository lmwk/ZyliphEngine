#pragma once

#include <glad/glad.h>

#include "../Core/Core.h"
#include "../Windowing/Window.h"
#include "../Layers/LayerStack.h"

#include "../ImGui/GUILayer.h"
#include "../HeaderFiles/Camera.h"

#include "../HeaderFiles/ZModel.h"

namespace Zyliph
{

    class  TestApp
    {
    public:
        TestApp();
        virtual ~TestApp();

        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        inline static TestApp& Get() { return *z_Instance; }
        inline Window& GetWindow() { return *z_Window; }
    private:
        bool OnWindowClosed(WindowCloseEvent& e);

        Scope<Window> z_Window;
        GUILayer* z_GuiLayer;
        bool z_Running = true;
        LayerStack z_LayerStack;
        Camera camera;
    private:
        static TestApp* z_Instance;
    };

    TestApp* CreateApp();
}
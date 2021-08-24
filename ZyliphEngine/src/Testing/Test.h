#pragma once

#include "../Core/Core.h"
#include "../Windowing/Window.h"
#include "../Layers/LayerStack.h"

namespace Zyliph
{

    class Z_API TestApp
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
        bool z_Running = true;
        LayerStack z_LayerStack;
    private:
        static TestApp* z_Instance;
    };

    TestApp* CreateApp();
}
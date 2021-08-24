#include "Test.h"


namespace Zyliph
{

    TestApp* TestApp::z_Instance = nullptr;

   TestApp::TestApp()
   {
       Z_CORE_ASSERT(!z_Instance, "Application already exists")
       z_Instance = this;

       ZLogger::Init();
       z_Window = Window::Create();
       z_Window->SetEventCallback(Z_BIND_EVENT_FN(OnEvent));
   }

    TestApp::~TestApp()
    {
        
    }

    void TestApp::PushLayer(Layer* layer)
    {
        z_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void TestApp::PushOverlay(Layer* layer)
    {
        z_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void TestApp::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(Z_BIND_EVENT_FN(OnWindowClosed));

        Z_CORE_INFO("{0}", e);

       for (auto it = z_LayerStack.end(); it != z_LayerStack.begin();)
       {
           (*--it)->OnEvent(e);
           if (e.handled)
               break;
       }
    }

    bool TestApp::OnWindowClosed(WindowCloseEvent& e)
    {
        z_Running = false;
        return true;
    }


    void TestApp::Run()
    {
        while (z_Running)
        {
            z_Window->OnUpdate();

            for (Layer* layer : z_LayerStack)
                layer->OnUpdate();

        }
    }
}

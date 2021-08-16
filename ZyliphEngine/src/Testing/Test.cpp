#include "Test.h"

#include <iostream>


namespace Zyliph
{
   TestApp::TestApp()
   {
       ZLogger::Init();
       z_Window = Window::Create();
       z_Window->SetEventCallback(Z_BIND_EVENT_FN(OnEvent));
   }

    TestApp::~TestApp()
    {
        
    }

    void TestApp::OnEvent(Event& e)
    {
        Z_CORE_INFO("{0}", e);
    }


    void TestApp::Run()
    {
        while (z_Running)
        {
            z_Window->OnUpdate();
        }
    }
}

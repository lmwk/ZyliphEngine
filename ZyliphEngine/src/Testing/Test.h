#pragma once

#include "../Core/Core.h"
#include "../Windowing/Window.h"

namespace Zyliph
{

    class Z_API TestApp
    {
    public:
        TestApp();
        virtual ~TestApp();

        void Run();

        void OnEvent(Event& e);
    private:
        Scope<Window> z_Window;
        bool z_Running = true;
    };

    TestApp* CreateApp();
}
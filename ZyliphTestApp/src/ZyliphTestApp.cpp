#include "Common.h"

class ExampleLayer : public Zyliph::Layer
{
public:
    ExampleLayer() : Layer("Example")
    {
    }

    void OnUpdate() override
    {
        if (Zyliph::Input::IsKeyPressed(L))
        {
            Z_CLIENT_TRACE("key L was pressed");
        }
    }

    void OnEvent(Zyliph::Event& event) override
    {
        
    }
};

class App : public Zyliph::TestApp
{
public:
    App()
    {
        PushLayer(new ExampleLayer());
    }

    ~App()
    {
        
    }

     
};

int main()
{
    App* app = new App();
    app->Run();
    delete app;
}
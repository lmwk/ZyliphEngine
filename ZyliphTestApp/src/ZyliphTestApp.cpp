#include "../../ZyliphEngine/src/Common.h"

class App : public Zyliph::TestApp
{
public:
    App()
    {
        
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
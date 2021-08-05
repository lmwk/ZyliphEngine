#ifndef ZGLFWINDOW_CLASS_H
#define ZGLFWINDOW_CLASS_H

#include "BaseWindow.h"
#include <memory>
#include "ZUIContext.h"
#include "ZOpenGLContext.h"
#include "ZScene.h"
#include "ZPropertyPanel.h"

class ZGLFWindow : public bWindow
{
public:

    ZGLFWindow() : IsRunning(true), Window(NULL)
    {
        ZUIctx = std::make_unique<ZUIContext>();
        ZRenderCtx = std::make_unique<ZOpenGLContext>();
    }

    bool init(int width, int height, const std::string& title);

    void render();

    void HandleInput();

    void* GetWindow() override { return Window; }

    void SetWindow(void* window)
    {
        Window = static_cast<GLFWwindow*>(window);
    }



    bool IsWindowRunning() { return IsRunning; }

private:
    GLFWwindow* Window;

    std::unique_ptr<ZUIContext> ZUIctx;

    std::unique_ptr<ZOpenGLContext> ZRenderCtx;

    std::unique_ptr<ZScene> ZScene;

    std::unique_ptr<ZPropertyPanel> zPropertyPanel;

    bool IsRunning;
};

#endif

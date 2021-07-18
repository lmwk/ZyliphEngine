#include "../HeaderFiles/ZGLFWindow.h"

bool ZGLFWindow::init(int width, int height, const std::string& title)
{
    Width = width;
    Height = height;
    Title = title;

    ZRenderCtx->init(this);

    ZUIctx->init(this);

    ZScene = std::make_unique<class ZScene>();

    zPropertyPanel = std::make_unique<ZPropertyPanel>();

    return IsRunning;
}

#ifndef BASERENDER_CLASS_H
#define BASERENDER_CLASS_H

#include "BaseWindow.h"

class ZRenderContext
{
public:

    ZRenderContext() : baseWindow(NULL) {}

    virtual bool init(bWindow* window)
    {
        baseWindow = window;
        return true;
    }

    virtual void pre_render() = 0;

    virtual void post_render() = 0;

    virtual void end() = 0;

protected:
    bWindow* baseWindow;
};

#endif
#ifndef BASERENDER_CLASS_H
#define BASERENDER_CLASS_H

#include "BaseWindow.h"

class FrameBuffer
{
public:
    FrameBuffer() : zFBO{ 0 } {}

    virtual void CreateBuffers(int width, int height) = 0;

    virtual void DeleteBuffers() = 0;

    virtual void Bind() = 0;

    virtual void UnBind() = 0;

    virtual unsigned int GetTexture() = 0;

protected:
    unsigned int zFBO = 0;
    int zWidth = 0;
    int zHeight = 0;
    unsigned int zTexId = 0;
    unsigned int zDepthId = 0;
};

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
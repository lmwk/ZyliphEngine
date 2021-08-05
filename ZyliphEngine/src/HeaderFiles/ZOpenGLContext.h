#ifndef ZOPENGLCONTEXT_CLASS_H
#define ZOPENGLCONTEXT_CLASS_H

#include "BaseRender.h"

class ZOpenGLContext : public ZRenderContext
{
public:

    bool init(bWindow* bwindow) override;

    void pre_render() override;

    void post_render() override;

    void end() override;
};

#endif
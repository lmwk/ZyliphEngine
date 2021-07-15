#ifndef ZUICONTEXT_CLASS_H
#define ZUICONTEXT_CLASS_H

#include "BaseRender.h"

class ZUIContext : public ZRenderContext
{
public:
    bool init(bWindow* window) override;

    void pre_render() override;

    void post_render() override;

    void end() override;

};

#endif
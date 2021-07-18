#ifndef ZPOSTPROCESSINGBUFFER_CLASS_H
#define ZPOSTPROCESSINGBUFFER_CLASS_H

#include "BaseRender.h"

class ZPostProcessingBuffer : public FrameBuffer
{
public:

    void CreateBuffers(int width, int height) override;

    void DeleteBuffers() override;

    void Bind() override;

    void UnBind() override;

    unsigned int GetTexture() override;

};

#endif
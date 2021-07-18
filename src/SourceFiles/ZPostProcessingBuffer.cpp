#include "../HeaderFiles/ZPostProcessingBuffer.h"

void ZPostProcessingBuffer::CreateBuffers(int width, int height)
{
    zWidth = width;
    zHeight = height;

    if (zFBO)
    {
        DeleteBuffers();
    }

    glGenFramebuffers(1, &zFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, zFBO);
    glGenTextures(GL_TEXTURE_2D, &zTexId);
    glBindTexture(GL_TEXTURE_2D, zTexId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, zWidth, zHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, zTexId, 0);

    glGenTextures(GL_TEXTURE_2D, &zDepthId);
    glBindTexture(GL_TEXTURE_2D, zDepthId);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, zWidth, zHeight);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, zDepthId, 0);

    GLenum buffers[4] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(zTexId, buffers);

    UnBind();
}

void ZPostProcessingBuffer::DeleteBuffers()
{
    if (zFBO)
    {
        glDeleteFramebuffers(GL_FRAMEBUFFER, &zFBO);
        glDeleteTextures(1, &zTexId);
        glDeleteTextures(1, &zDepthId);
        zTexId = 0;
        zDepthId = 0;
    }
}

void ZPostProcessingBuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, zFBO);
    glViewport(0, 0, zWidth, zHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ZPostProcessingBuffer::UnBind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int ZPostProcessingBuffer::GetTexture()
{
    return zTexId;
}


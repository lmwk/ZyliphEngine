#ifndef BASEWINDOW_CLASS_H
#define BASEWINDOW_CLASS_H

#include <string>
#include <GLFW/glfw3.h>

class bWindow
{
public:

    virtual void* GetWindow();

    virtual void SetWindow(void* window) = 0;

    virtual void OnResize(int width, int height) = 0;

    virtual void SetWindowPos(int xpos, int ypos);

    int Width;
    int Height;
    std::string Title;
};

#endif

#ifndef BASEWINDOW_CLASS_H
#define BASEWINWO_CLASS_H

#include <string>
#include <GLFW/glfw3.h>

class bWindow
{
public:

    

    virtual void OnResize(GLFWwindow* window,int width, int height) = 0;

    virtual void SetWindowPos(GLFWwindow* window, int xpos, int ypos);

    virtual void OnWindowMaximize(GLFWwindow* window, int maximized);

    virtual void WindowFocus(GLFWwindow* window, int focused);

    int Width;
    int Height;
    std::string Title;
};

#endif

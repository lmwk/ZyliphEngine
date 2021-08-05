#include "../HeaderFiles/ZOpenGLContext.h"

#include <iostream>
#include "glad/glad.h"

static void on_resize_callback(GLFWwindow* window, int width, int height)
{
    auto zwindow = static_cast<bWindow*>(glfwGetWindowUserPointer(window));
    zwindow->OnResize(width, height);
}

static void set_window_pos(GLFWwindow* window, int xpos, int ypos)
{
    auto zwindow = static_cast<bWindow*>(glfwGetWindowUserPointer(window));
    zwindow->SetWindowPos(xpos, ypos);
}

bool ZOpenGLContext::init(bWindow* bwindow)
{
    __super::init(bwindow);


    if (!glfwInit())
    {
        // create a logger
        std::cout << "Error: GLFW couldn't be initialized" << std::endl;
        return false;
    }


    auto glWindow = glfwCreateWindow(bwindow->Width, bwindow->Height, bwindow->Title.c_str(), NULL, NULL);
    bwindow->SetWindow(glWindow);

    if (!glWindow)
    {
        // create a logger
        std::cout << "Error: GLFW window couldn't be created" << std::endl;
        return false;
    }

    glfwSetWindowSizeCallback(glWindow, on_resize_callback);
    glfwSetWindowPosCallback(glWindow, set_window_pos);
    glfwMakeContextCurrent(glWindow);

    gladLoadGL();

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

void ZOpenGLContext::pre_render()
{
    glViewport(0, 0, baseWindow->Width, baseWindow->Height);
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void ZOpenGLContext::post_render()
{
    glfwPollEvents();
    glfwSwapBuffers((GLFWwindow*)baseWindow->GetWindow());
}

void ZOpenGLContext::end()
{
    glfwDestroyWindow((GLFWwindow*)baseWindow->GetWindow());
    glfwTerminate();
}


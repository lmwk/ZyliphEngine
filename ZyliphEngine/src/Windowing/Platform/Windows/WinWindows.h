#pragma once

#include "../../Window.h"

#include "../../../Rendering/GraphicsContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Zyliph
{
    class WinWindow : public Window
    {
    public:
        WinWindow(const WindowVals& vals);
        virtual ~WinWindow();

        void OnUpdate() override;

        inline unsigned int GetWidth() const override { return z_Data.Width; }
        inline unsigned int GetHeight() const override { return z_Data.Height; }

        inline void SetEventCallback(const EventCallbackFn& callback) override { z_Data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        inline virtual void* GetNativeWindow() const { return z_Window; };
    private:
        virtual void Init(const WindowVals& vals);
        virtual void Shutdown();
    private:
        GLFWwindow* z_Window;
        GraphicsContext* z_RenderCtx;

        struct WindowData
        {
            std::string title;
            unsigned int Width, Height;
            bool Vsync;

            EventCallbackFn EventCallback;
        };

        WindowData z_Data;
    };
}

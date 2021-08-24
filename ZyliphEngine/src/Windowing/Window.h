#pragma once

#include "../Core/Assert.h"
#include "../Events/Event.h"
#include "../Events/AppEvent.h"
#include "../Events/MouseEvent.h"
#include "../Events/KeyEvent.h"

namespace Zyliph
{
    struct WindowVals
    {
        std::string Title;
        unsigned int width;
        unsigned int height;

        WindowVals(const std::string& title = "Zyliph Engine", 
            unsigned int Width = 1280, 
            unsigned int Height = 720)
        : Title(title), width(Width), height(Height) {}
    };

    class Z_API Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() = default;

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void* GetNativeWindow() const = 0;

        static Scope<Window> Create(const WindowVals& vals = WindowVals());
    };
}
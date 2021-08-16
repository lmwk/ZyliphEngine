#pragma once

#include "Event.h"

#include <sstream>

namespace Zyliph
{
    class Z_API WindowResizeEvent : public Event 
    {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height) : z_Width(width), z_Height(height) {}

        inline unsigned int GetW() const { return z_Width; }
        inline unsigned int GetH() const { return z_Height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << z_Width << ", " << z_Height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryApp)
    private:
        unsigned int z_Width, z_Height;
    };

    class Z_API WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() = default;

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApp)
    };

    class Z_API AppTickEvent : public Event
    {
    public:
        AppTickEvent() = default;

        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategoryApp)
    };

    class Z_API AppUpdateEvent : public Event
    {
    public:
        AppUpdateEvent() = default;

        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(EventCategoryApp)
    };

    class Z_API AppRenderEvent : public Event
    {
    public:
        AppRenderEvent() = default;

        EVENT_CLASS_TYPE(AppRender)
            EVENT_CLASS_CATEGORY(EventCategoryApp)
    };
}
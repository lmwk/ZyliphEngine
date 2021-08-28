#pragma once

#include "Event.h"

#include <sstream>

namespace Zyliph
{

    class  MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float x, float y) : z_MouseX(x), z_MouseY(y) {}

        inline float GetX() const { return z_MouseX; }
        inline float GetY() const { return z_MouseY; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << z_MouseX << ", " << z_MouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    private:
        float z_MouseX, z_MouseY;
    };

    class  MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float xOffset, float yOffset) : z_xOffset(xOffset), z_yOffset(yOffset) {}

        inline float GetXOffset() const { return z_xOffset; }
        inline float GetYOffset() const { return z_yOffset; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    private:
        float z_xOffset, z_yOffset;
    };

    class  MouseButtonEvent : public Event
    {
    public:
        inline int GetMouseButton() const { return z_Button; }

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    protected:
        MouseButtonEvent(int button) : z_Button(button) {}
        int z_Button;
    };

    class  MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << z_Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class  MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << z_Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };

}

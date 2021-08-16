#pragma once

#include "Event.h"

#include <sstream>

namespace Zyliph
{
    class Z_API KeyEvent : public Event
    {
    public:
        inline int GetKeyCode() const { return z_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
    protected:
        KeyEvent(int keycode) : z_KeyCode(keycode) {}

        int z_KeyCode;
    };

    class Z_API KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), z_RepeatCount(repeatCount) {}

        inline int GetRepeatCount() const{ return z_RepeatCount; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << z_KeyCode << " (" << z_RepeatCount << " repeats";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
    private:
        int z_RepeatCount;
    };

    class Z_API KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << z_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };
}
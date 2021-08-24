#pragma once

#include "../Core/Core.h"
#include "glm/glm.hpp"

namespace Zyliph
{
    class Z_API Input
    {
    public:
        inline static bool IsKeyPressed(int keycode) { return z_Instance->IsKeyPressedImpl(keycode); }
        inline static bool IsMouseButtonPressed(int button) { return z_Instance->IsMouseButtonPressedImpl(button); }
        inline static glm::vec2 GetMousePos() { return z_Instance->GetMousePosImpl(); }
        inline static float GetMouseX() { return z_Instance->GetMouseXImpl(); }
        inline static float GetMouseY() { return z_Instance->GetMouseYImpl(); }
    protected:
        virtual bool IsKeyPressedImpl(int keycode) = 0;

        virtual bool IsMouseButtonPressedImpl(int button) = 0;
        virtual glm::vec2 GetMousePosImpl() = 0;
        virtual float GetMouseXImpl() = 0;
        virtual float GetMouseYImpl() = 0;
    private:
        static Input* z_Instance;
    };
}
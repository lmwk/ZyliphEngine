#pragma once

#include "../../../Utils/Input.h"

namespace Zyliph
{
    class WindowsInput : public Input
    {
    public:

    protected:
        virtual bool IsKeyPressedImpl(int keycode) override;

        bool IsMouseButtonPressedImpl(int button) override;
        float GetMouseXImpl() override;
        float GetMouseYImpl() override;
        glm::vec2 GetMousePosImpl() override;
    };
}
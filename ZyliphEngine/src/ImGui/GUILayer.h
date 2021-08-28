#pragma once

#include <glad/glad.h>

#include "../Layers/Layer.h"

#include "../Events/AppEvent.h"
#include "../Events/KeyEvent.h"
#include "../Events/MouseEvent.h"

namespace Zyliph
{
    class  GUILayer : public Layer
    {
    public:

        GUILayer();
        ~GUILayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();
    private:
        float z_Time = 0.0f;
    };

}
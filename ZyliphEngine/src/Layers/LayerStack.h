#pragma once

#include "../Core/Core.h"
#include "Layer.h"

#include <vector>

namespace Zyliph
{
    class Z_API LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        std::vector<Layer*>::iterator begin() { return z_Layers.begin(); }
        std::vector<Layer*>::iterator end() { return z_Layers.end(); };
    private:
        std::vector<Layer*> z_Layers;
        std::vector<Layer*>::iterator z_LayerInsert;
    };
}
#include "LayerStack.h"

namespace Zyliph
{
    LayerStack::LayerStack()
    {
    }

    LayerStack::~LayerStack()
    {
        for (Layer* layer : z_Layers)
            delete layer;
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        z_Layers.emplace(z_Layers.begin() + z_LayerInsertIndex, layer);
        z_LayerInsertIndex++;
    }

    void LayerStack::PushOverlay(Layer* overlay)
    {
        z_Layers.emplace_back(overlay);
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        auto it = std::find(z_Layers.begin(), z_Layers.end(), layer);
        if (it != z_Layers.end())
        {
            z_Layers.erase(it);
            z_LayerInsertIndex--;
        }
    }

    void LayerStack::PopOverlay(Layer* overlay)
    {
        auto it = std::find(z_Layers.begin(), z_Layers.end(), overlay);
        if (it != z_Layers.end())
        {
            z_Layers.erase(it);
        }
    }
}

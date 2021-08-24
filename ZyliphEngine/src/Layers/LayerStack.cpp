#include "LayerStack.h"

namespace Zyliph
{
    LayerStack::LayerStack()
    {
        z_LayerInsert = z_Layers.begin();
    }

    LayerStack::~LayerStack()
    {
        for (Layer* layer : z_Layers)
            delete layer;
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        z_LayerInsert = z_Layers.emplace(z_LayerInsert, layer);
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
            z_LayerInsert--;
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

#pragma once

#include "../Core/Core.h"
#include <sstream>
#include "../Events/Event.h"

namespace Zyliph
{
    class Z_API Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnEvent(Event& event) {}

        inline const std::string& GetName() const { return z_DebugName; }
    protected:
        std::string z_DebugName;
    };
}
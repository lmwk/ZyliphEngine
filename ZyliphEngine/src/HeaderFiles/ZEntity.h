#ifndef ZENTITY_CLASS_H
#define ZENTITY_CLASS_H

#include "entt/entt.hpp"
#include "Components.h"

namespace Zyliph
{
    class ZEntity
    {
    public:
        ZEntity() = default;
        ZEntity(entt::entity handle);
        ZEntity(const ZEntity& other) = default;

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args)
        {
            
        }

        template<typename T>
        T& GetComponent()
        {
            
        }

        template<typename T>
        bool HasComponent()
        {
            return true;
        }

        template<typename T>
        void RemoveComponent()
        {
             
        }

        operator bool() const { return z_EntityH != entt::null; }

    private:
        entt::entity z_EntityH{ entt::null };
    };
}
#endif
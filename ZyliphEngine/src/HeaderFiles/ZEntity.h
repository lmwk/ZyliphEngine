#ifndef ZENTITY_CLASS_H
#define ZENTITY_CLASS_H

#include "entt/entt.hpp"
#include "ZScene.h"
#include "Components.h"

namespace Zyliph
{
    class ZEntity
    {
    public:
        ZEntity() = default;
        ZEntity(entt::entity handle, ZScene* scene);
        ZEntity(const ZEntity& other) = default;

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args)
        {
            return z_Scene->zManager->emplace<T>(z_EntityH, std::forward<Args>(args)...);
        }

        template<typename T>
        T& GetComponent()
        {
            return z_Scene->zManager.get<T>(z_EntityH);
        }

        template<typename T>
        bool HasComponent()
        {
            return z_Scene->zManager->all_of<T>(z_EntityH);
        }

        template<typename T>
        void RemoveComponent()
        {
            z_Scene->zManager->remove<T>(z_EntityH);
        }

        operator bool() const { return z_EntityH != entt::null; }

    private:
        entt::entity z_EntityH{ entt::null };
        ZScene* z_Scene = nullptr;
    };
}
#endif
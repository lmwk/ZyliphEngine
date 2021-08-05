#include "../HeaderFiles/ZScene.h"
#include "../HeaderFiles/ZEntity.h"
#include "../HeaderFiles/Components.h"

ZEntity ZScene::create_entity(std::string name)
{
    ZEntity entity{ zManager->create(), this };
    entity.AddComponent<IdentifierComponent>(name);

    return entity;
}

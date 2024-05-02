#include "World.h"

#include "../../Interfaces/ICollision.h"
#include "../Object/Object.h"

void World::Update(const float deltaTime)
{
    for (const auto& object : _objects) object->Update(deltaTime);
}

void World::FixedUpdate()
{
    for (const auto& object : _objects) object->FixedUpdate();
}

void World::Render(IDraw* renderSystem)
{
    for (const auto& object : _objects) object->Render(renderSystem);
}

const Dosuha::Vector<ICollision*>& World::GetCollisions() const
{
    return _collisions;
}

void World::AddObject(Object* object)
{
    if (ICollision* collision = dynamic_cast<ICollision*>(object)) _collisions.PushBack(collision);
    _objects.PushBack(object);
}

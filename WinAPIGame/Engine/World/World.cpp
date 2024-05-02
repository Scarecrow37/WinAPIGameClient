#include "World.h"

#include "../../Interfaces/ICollision.h"
#include "../Object/Object.h"

void World::Update(const float deltaTime)
{
    for (const auto& object : _objects) if (object) object->Update(deltaTime);
}

void World::FixedUpdate()
{
    for (const auto& object : _objects) if (object) object->FixedUpdate();
}

void World::Render(IDraw* renderSystem)
{
    for (const auto& object : _objects) if (object) object->Render(renderSystem);
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

void World::RemoveObject(Object* object)
{
    for (size_t i = 0; i < _objects.Size(); ++i)
    {
        if (_objects[i] == object) _objects[i] = nullptr;
    }
    for (size_t i = 0; i < _collisions.Size(); ++i)
    {
        if (_collisions[i] == dynamic_cast<ICollision*>(object)) _collisions[i] = nullptr;
    }
}

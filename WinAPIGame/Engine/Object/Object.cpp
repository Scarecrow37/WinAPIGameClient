#include "Object.h"

#include "../Components/Component.h"

Object::Object() : _transform({})
{
}

Object::Object(const Transform& transform) : _transform(transform)
{
}

void Object::Update(const float deltaTime)
{
    for (const auto& component : _components) component->Update(deltaTime);
}

void Object::FixedUpdate()
{
    for (const auto& component : _components) component->FixedUpdate();
}

void Object::Render(IDraw* renderSystem)
{
    for (const auto& component : _components) component->Render(renderSystem);
}

void Object::AddComponent(Component* component)
{
    _components.PushBack(component);
}

Transform Object::GetTransform()
{
    return _transform;
}

#pragma once
#include "IContainObjects.h"
#include "../../Containers/Vector.h"
#include "../../Interfaces/IDeltaUpdate.h"
#include "../../Interfaces/IFixedUpdate.h"
#include "../../Interfaces/IRender.h"

class ICollision;
class Object;

class World final : public IDeltaUpdate, public IFixedUpdate, public IRender, public IContainObjects
{
public:
    void Update(float deltaTime) override;
    void FixedUpdate() override;
    void Render(IDraw* renderSystem) override;

    const Dosuha::Vector<ICollision*>& GetCollisions() const override;
    void AddObject(Object* object) override;

private:
    Dosuha::Vector<Object*> _objects;
    Dosuha::Vector<ICollision*> _collisions;
};

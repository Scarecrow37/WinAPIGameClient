#pragma once
#include "IContainComponents.h"
#include "../../Containers/Vector.h"
#include "../../Interfaces/IDeltaUpdate.h"
#include "../../Interfaces/IFixedUpdate.h"
#include "../../Interfaces/IRender.h"
#include "../../Interfaces/ITransform.h"

class Object : public IDeltaUpdate, public IFixedUpdate, public IRender, public IContainComponents, public ITransform
{
public:
    Object();
    Object(const Transform& transform);

    void Update(float deltaTime) override;
    void FixedUpdate() override;
    void Render(IDraw* renderSystem) override;

    void AddComponent(Component* component) final;

    Transform GetTransform() override;

protected:
    Transform _transform;

private:
    Dosuha::Vector<Component*> _components;
};

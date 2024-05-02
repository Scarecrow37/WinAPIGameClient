#pragma once
#include "../Containers/Vector.h"

class Collider;
class ICollision;

class CollisionManager
{
public:
    void CollisionUpdate(const Dosuha::Vector<ICollision*>& collisions);

private:
    bool CollisionCheck(Collider* a, Collider* b);
};

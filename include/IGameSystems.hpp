#pragma once
#include "Entities.hpp"


class IGameSystems {
    public:
    ~IGameSystems(){};

    virtual void InputSystem(Entity* entity) = 0;
    virtual void SoundSystem(Entity* entity) = 0;
    virtual void PhysicsSystem(Entity* entity) = 0;
    virtual void ExpireSystem(Entity* entity) = 0;
    virtual void TweenSystem(Entity* entity) = 0;
    virtual void RemoveSystem(Entity* entity) = 0;
    virtual void SpawnSystem(Entity* entity) = 0;
    virtual void EntitySystem(Entity* entity) = 0;
    virtual void CollisionSystem(Entity* entity) = 0;

    virtual double SpawnEnemy(double delta, double t, int enemy) = 0;
    virtual void HandleCollision(Entity* a, Entity* b) = 0;

};


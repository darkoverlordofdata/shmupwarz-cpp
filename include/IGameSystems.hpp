#pragma once
#include "Entities.hpp"


class IGameSystems {
    public:
    ~IGameSystems(){};

    virtual void InputSystem(Entity* entity){};
    virtual void SoundSystem(Entity* entity){};
    virtual void PhysicsSystem(Entity* entity){};
    virtual void ExpireSystem(Entity* entity){};
    virtual void TweenSystem(Entity* entity){};
    virtual void RemoveSystem(Entity* entity){};
    virtual void SpawnSystem(Entity* entity){};
    virtual void EntitySystem(Entity* entity){};
    virtual void CollisionSystem(Entity* entity){};

    virtual double SpawnEnemy(double delta, double t, int enemy){};
    virtual bool Intersects(SDL_Rect* r1, SDL_Rect* r2){};
    virtual void HandleCollision(Entity* a, Entity* b){};

};


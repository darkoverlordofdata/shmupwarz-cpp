#pragma once
#include "Entities.hpp"


class IGameSystems {
    public:
    ~IGameSystems(){};

    void InputSystem(Entity* entity){};
    void SoundSystem(Entity* entity){};
    void PhysicsSystem(Entity* entity){};
    void ExpireSystem(Entity* entity){};
    void TweenSystem(Entity* entity){};
    void RemoveSystem(Entity* entity){};
    void SpawnSystem(Entity* entity){};
    void EntitySystem(Entity* entity){};
    void CollisionSystem(Entity* entity){};

    double SpawnEnemy(double delta, double t, int enemy){};
    bool Intersects(SDL_Rect* r1, SDL_Rect* r2){};
    void HandleCollision(Entity* a, Entity* b){};

};


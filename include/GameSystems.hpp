#pragma once
#include "Shmupwarz.hpp"
#include "Entities.hpp"

class Shmupwarz;

class GameSystems {
public:
    GameSystems(Shmupwarz* game);
    ~GameSystems();

    void InputSystem(Entity* entity);
    void SoundSystem(Entity* entity);
    void PhysicsSystem(Entity* entity);
    void ExpireSystem(Entity* entity);
    void TweenSystem(Entity* entity);
    void RemoveSystem(Entity* entity);
    void SpawnSystem(Entity* entity);
    void EntitySystem(Entity* entity);
    void CollisionSystem(Entity* entity);

    double SpawnEnemy(double delta, double t, int enemy);
    bool Intersects(SDL_Rect* r1, SDL_Rect* r2);
    void HandleCollision(Entity* a, Entity* b);

private:
    Shmupwarz* Game;
    double FireRate = 0.1;
    double TimeToFire = 0.0;
    double EnemyT1 = 1.0;
    double EnemyT2 = 4.0;
    double EnemyT3 = 6.0;
    Mix_Chunk* Pew;
    Mix_Chunk* Asplode;
    Mix_Chunk* Smallasplode;
};


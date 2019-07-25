#include "Shmupwarz.hpp"
#include "IGameSystems.hpp"

class GameSystems : public IGameSystems {
    public:
    Shmupwarz* mGame;
    double FireRate = 0.1;
    double TimeToFire = 0.0;
    double EnemyT1 = 1.0;
    double EnemyT2 = 4.0;
    double EnemyT3 = 6.0;
    Mix_Chunk* Pew;
    Mix_Chunk* Asplode;
    Mix_Chunk* Smallasplode;


    GameSystems(Shmupwarz* g): mGame(g) {
        Pew = Mix_LoadWAV("assets/Sounds/pew.wav");
        Asplode = Mix_LoadWAV("assets/Sounds/asplode.wav");
        Smallasplode = Mix_LoadWAV("assets/Sounds/smallasplode.wav");
    }
    // ~GameSystems(){}

    void InputSystem(Entity* entity){
        entity->Position.X = mGame->MouseX();
        entity->Position.Y = mGame->MouseY();
        if (mGame->GetKey(122) || mGame->MouseDown()) {
            TimeToFire -= mGame->Delta();
            if (TimeToFire < 0.0) {
                mGame->Bullets.emplace_back(entity->Position.X - 27, entity->Position.Y + 2);
                mGame->Bullets.emplace_back(entity->Position.X + 27, entity->Position.Y + 2);
                TimeToFire = FireRate;
            }
        }
    }

    void SoundSystem(Entity* entity){
        if (entity->Active && entity->Sound) {
            switch(entity->Sound.value()) {
                case Effect::PEW: 
                    Mix_PlayChannelTimed(-1, Pew, 0, 0);
                    break;

                case Effect::ASPLODE: 
                    Mix_PlayChannelTimed(-1, Asplode, 0, 0);
                    break;

                case Effect::SMALLASPLODE: 
                    Mix_PlayChannelTimed(-1, Smallasplode, 0, 0);
                    break;
            }
        }
    }

    void PhysicsSystem(Entity* entity){
        if (entity->Active)
        {
            // Move entity?
            if (entity->Velocity) {
                entity->Position.X += entity->Velocity.value()->X * mGame->Delta();
                entity->Position.Y += entity->Velocity.value()->Y * mGame->Delta();
            }
            // Set new bounding box
            if (entity->Category == CategoryOf::BACKGROUND) 
            {
                // entity->Bounds.w = entity->Sprite.width * entity->Scale.X;
                // entity->Bounds.h = entity->Sprite.height * entity->Scale.Y;
                entity->Bounds.w = mGame->Width();
                entity->Bounds.h = mGame->Height();
                entity->Bounds.x = 0; 
                entity->Bounds.y = 0; 
            } else {
                entity->Bounds.w = entity->Sprite.Width * entity->Scale.X;
                entity->Bounds.h = entity->Sprite.Height * entity->Scale.Y;
                entity->Bounds.x = entity->Position.X - entity->Bounds.w / 2;
                entity->Bounds.y = entity->Position.Y - entity->Bounds.h / 2;
            }
        }
    }

    void ExpireSystem(Entity* entity){
        if (entity->Active && entity->Expires) {
            auto exp = entity->Expires.value() - mGame->Delta();
            entity->Expires = exp;
            if (entity->Expires.value() < 0) {
                entity->Active = false;
            }
        }
    }

    void TweenSystem(Entity* entity){
        if (entity->Active && entity->Tween) {

            auto x = entity->Scale.X + (entity->Tween.value()->Speed * mGame->Delta());
            auto y = entity->Scale.Y + (entity->Tween.value()->Speed * mGame->Delta());
            auto Active = entity->Tween.value()->Active;


            if (x > entity->Tween.value()->Max) {
                x = entity->Tween.value()->Max;
                y = entity->Tween.value()->Max;
                Active = false;
            } else if (x < entity->Tween.value()->Min) {
                x = entity->Tween.value()->Min;
                y = entity->Tween.value()->Min;
                Active = false;
            }
            entity->Scale.X = x; 
            entity->Scale.Y = y; 
            entity->Tween = new Tween(entity->Tween.value()->Min, 
                                        entity->Tween.value()->Max, 
                                        entity->Tween.value()->Speed, 
                                        entity->Tween.value()->Repeat, Active);
        }
    }

    void RemoveSystem(Entity* entity){
        if (entity->Active) {
            switch(entity->Category) {
                case CategoryOf::ENEMY:
                    if (entity->Position.Y > mGame->Height()) {
                        entity->Active = false;
                    }
                    break;
                case CategoryOf::BULLET:
                    if (entity->Position.Y < 0) {
                        entity->Active = false;
                    }
                    break;
                default:
                    break;
            }
        }
    }

    double SpawnEnemy(double delta, double t, int enemy) {
        auto d1 = t-delta;
        if (d1 < 0.0) {
            switch(enemy) {
                case 1:
                    mGame->Enemies1.emplace_back((std::rand() % (mGame->Width()-70))+35, 35);
                    return 1.0;
                case 2:
                    mGame->Enemies2.emplace_back((std::rand() % (mGame->Width()-170))+85, 85);
                    return 4.0;
                case 3:
                    mGame->Enemies3.emplace_back((std::rand() % (mGame->Width()-320))+160, 160);
                    return 6.0;
                default:
                    return 0;
            }
        } else return d1;    
    }

    void SpawnSystem(Entity* entity){
        EnemyT1 = SpawnEnemy(mGame->Delta(), EnemyT1, 1);
        EnemyT2 = SpawnEnemy(mGame->Delta(), EnemyT2, 2);
        EnemyT3 = SpawnEnemy(mGame->Delta(), EnemyT3, 3);

    }

    void EntitySystem(Entity* entity){
        if (!entity->Active) {
            switch(entity->Type) {

                case TypeOf::BULLET: 
                    if (mGame->Bullets.empty()) break;
                    RefreshBullet(entity, mGame->Bullets.back().X, mGame->Bullets.back().Y);
                    mGame->Bullets.pop_back();
                    break;

                case TypeOf::ENEMY1:
                    if (mGame->Enemies1.empty()) break;
                    RefreshEnemy1(entity, mGame->Enemies1.back().X, mGame->Enemies1.back().Y);
                    mGame->Enemies1.pop_back();
                    break;

                case TypeOf::ENEMY2:
                    if (mGame->Enemies2.empty()) break;
                    RefreshEnemy2(entity, mGame->Enemies2.back().X, mGame->Enemies2.back().Y);
                    mGame->Enemies2.pop_back();
                    break;

                case TypeOf::ENEMY3:
                    if (mGame->Enemies3.empty()) break;
                    RefreshEnemy3(entity, mGame->Enemies3.back().X, mGame->Enemies3.back().Y);
                    mGame->Enemies3.pop_back();
                    break;

                case TypeOf::EXPLOSION:  
                    if (mGame->Explosions.empty()) break;
                    RefreshExplosion(entity, mGame->Explosions.back().X, mGame->Explosions.back().Y);
                    mGame->Explosions.pop_back();
                    break;

                case TypeOf::BANG:
                    if (mGame->Bangs.empty()) break;
                    RefreshBang(entity, mGame->Bangs.back().X, mGame->Bangs.back().Y);
                    mGame->Bangs.pop_back();
                    break;

                case TypeOf::PARTICLE:
                    if (mGame->Particles.empty()) break;
                    RefreshParticle(entity, mGame->Particles.back().X, mGame->Particles.back().Y);
                    mGame->Particles.pop_back();
                    break;

                default:
                    break;
            }
        }

    }

    void HandleCollision(Entity* a, Entity* b){
        mGame->Bangs.emplace_back(b->Bounds.x, b->Bounds.y);
        b->Active = false;
        for (int i=0; i<3; i++) mGame->Particles.emplace_back(b->Bounds.x, b->Bounds.y);
        if (a->Health) {
            auto h = a->Health.value()->Current - 2;
            if (h < 0) {
                mGame->Explosions.emplace_back(a->Position.X, a->Position.Y);
                a->Active = false;
            } else {
                a->Health = new Health(h, a->Health.value()->Maximum);
            }   
        }
    }


    void CollisionSystem(Entity* entity){
        if (entity->Active && entity->Category == CategoryOf::ENEMY) {
            for (int i=0; i<mGame->Entities.size(); i++) {
                auto bullet = &mGame->Entities[i];
                if (bullet->Active && bullet->Category == CategoryOf::BULLET) {
                    if (SDL_HasIntersection(&entity->Bounds, &bullet->Bounds)) {
                        if (entity->Active && bullet->Active) HandleCollision(entity, bullet);
                        return;
                    }
                }
            }
        }
    }
};
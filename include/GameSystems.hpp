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
    // xna::graphics::SpriteRenderer* Renderer;


    GameSystems(Shmupwarz* g): mGame(g) {
        // Renderer = new xna::SpriteRenderer(xna::ResourceManager::GetShader("sprite"));

    }
    // ~GameSystems(){}

    void DrawSystem(xna::graphics::SpriteRenderer* Renderer, Entity* e) override {
        if (!e->Active) return;

        glm::vec3 color(1, 1, 1);

        auto texture = e->Transform.value()->Texture;
        if (e->Tint) {
            color[0] = (float)e->Tint.value()->R/255.0;
            color[1] = (float)e->Tint.value()->G/255.0;
            color[2] = (float)e->Tint.value()->B/255.0;
        }

        Renderer->DrawSprite(texture, 
            {   e->Transform.value()->Bounds.x, 
                e->Transform.value()->Bounds.y },
            {   e->Transform.value()->Bounds.w, 
                e->Transform.value()->Bounds.h }, 
            0.0f, color);


    }

    void InputSystem(Entity* entity) override {
        entity->Transform.value()->Pos.X = mGame->MouseX();
        entity->Transform.value()->Pos.Y = mGame->MouseY();
        if (mGame->GetKey(122) || mGame->MouseDown()) {
            TimeToFire -= mGame->Delta();
            if (TimeToFire < 0.0) {
                mGame->Bullets.emplace_back(entity->Transform.value()->Pos.X - 27, entity->Transform.value()->Pos.Y + 2);
                mGame->Bullets.emplace_back(entity->Transform.value()->Pos.X + 27, entity->Transform.value()->Pos.Y + 2);
                TimeToFire = FireRate;
            }
        }
    }

    void SoundSystem(Entity* entity) override {
        if (entity->Active && entity->Sound) {
            Mix_PlayChannelTimed(1, entity->Sound.value()->Chunk, 0, 0);
        }
    }

    void PhysicsSystem(Entity* entity) override {
        if (entity->Active)
        {
            // Move entity?
            if (entity->Velocity) {
                entity->Transform.value()->Pos.X += entity->Velocity.value()->X * mGame->Delta();
                entity->Transform.value()->Pos.Y += entity->Velocity.value()->Y * mGame->Delta();
            }
            // Set new bounding box
            if (entity->Identity.value()->Category == CategoryOf::BACKGROUND) 
            {
                entity->Transform.value()->Bounds.w = mGame->Width();
                entity->Transform.value()->Bounds.h = mGame->Height();
                entity->Transform.value()->Bounds.x = 0; 
                entity->Transform.value()->Bounds.y = 0; 
            } else {
                entity->Transform.value()->Bounds.w = entity->Transform.value()->Texture->Width * entity->Transform.value()->Scale.X;
                entity->Transform.value()->Bounds.h = entity->Transform.value()->Texture->Height * entity->Transform.value()->Scale.Y;
                entity->Transform.value()->Bounds.x = entity->Transform.value()->Pos.X - entity->Transform.value()->Bounds.w / 2;
                entity->Transform.value()->Bounds.y = entity->Transform.value()->Pos.Y - entity->Transform.value()->Bounds.h / 2;
            }
        }
    }

    void ExpireSystem(Entity* entity) override {
        if (entity->Active && entity->Expires) {
            auto exp = entity->Expires.value()->Milli - mGame->Delta();
            entity->Expires.value()->Milli = exp;
            if (entity->Expires.value()->Milli < 0) {
                entity->Active = false;
            }
        }
    }

    void TweenSystem(Entity* entity) override {
        if (entity->Active && entity->Tween) {

            auto x = entity->Transform.value()->Scale.X + (entity->Tween.value()->Speed * mGame->Delta());
            auto y = entity->Transform.value()->Scale.Y + (entity->Tween.value()->Speed * mGame->Delta());
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
            entity->Transform.value()->Scale.X = x; 
            entity->Transform.value()->Scale.Y = y; 
            entity->Tween = new Tween(entity->Tween.value()->Min, 
                                        entity->Tween.value()->Max, 
                                        entity->Tween.value()->Speed, 
                                        entity->Tween.value()->Repeat, Active);
        }
    }

    void RemoveSystem(Entity* entity) override {
        if (entity->Active) {
            switch(entity->Identity.value()->Category) {
                case CategoryOf::ENEMY:
                    if (entity->Transform.value()->Pos.Y > mGame->Height()) {
                        entity->Active = false;
                    }
                    break;
                case CategoryOf::BULLET:
                    if (entity->Transform.value()->Pos.Y < 0) {
                        entity->Active = false;
                    }
                    break;
                default:
                    break;
            }
        }
    }

    double SpawnEnemy(double delta, double t, int enemy) override {
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

    void SpawnSystem(Entity* entity) override {
        EnemyT1 = SpawnEnemy(mGame->Delta(), EnemyT1, 1);
        EnemyT2 = SpawnEnemy(mGame->Delta(), EnemyT2, 2);
        EnemyT3 = SpawnEnemy(mGame->Delta(), EnemyT3, 3);

    }

    void EntitySystem(Entity* entity) override {
        if (!entity->Active) {
            switch(entity->Identity.value()->Type) {

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

    void HandleCollision(Entity* a, Entity* b) override {
        mGame->Bangs.emplace_back(b->Transform.value()->Bounds.x, b->Transform.value()->Bounds.y);
        b->Active = false;
        for (int i=0; i<3; i++) mGame->Particles.emplace_back(b->Transform.value()->Bounds.x, b->Transform.value()->Bounds.y);
        if (a->Health) {
            auto h = a->Health.value()->Current - 2;
            if (h < 0) {
                mGame->Explosions.emplace_back(a->Transform.value()->Pos.X, a->Transform.value()->Pos.Y);
                a->Active = false;
            } else {
                a->Health = new Health(h, a->Health.value()->Maximum);
            }   
        }
    }


    void CollisionSystem(Entity* entity) override {
        if (entity->Active && entity->Identity.value()->Category == CategoryOf::ENEMY) {
            for (int i=0; i<mGame->Entities.size(); i++) {
                auto bullet = &mGame->Entities[i];
                if (bullet->Active && bullet->Identity.value()->Category == CategoryOf::BULLET) {
                    if (SDL_HasIntersection(&entity->Transform.value()->Bounds, &bullet->Transform.value()->Bounds)) {
                        if (entity->Active && bullet->Active) HandleCollision(entity, bullet);
                        return;
                    }
                }
            }
        }
    }
};
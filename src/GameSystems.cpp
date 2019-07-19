#include "Shmupwarz.hpp"
#include "GameSystems.hpp"

GameSystems::GameSystems(Shmupwarz* g): Game(g) {
    Pew = Mix_LoadWAV("assets/Sounds/pew.wav");
    Asplode = Mix_LoadWAV("assets/Sounds/asplode.wav");
    Smallasplode = Mix_LoadWAV("assets/Sounds/smallasplode.wav");
}
GameSystems::~GameSystems(){}

void GameSystems::InputSystem(Entity* entity){
    entity->Position.X = Game->MouseX();
    entity->Position.Y = Game->MouseY();
    if (Game->GetKey(122) || Game->MouseDown()) {
        TimeToFire -= Game->Delta();
        if (TimeToFire < 0.0) {
            Game->Bullets.emplace_back(entity->Position.X - 27, entity->Position.Y + 2);
            Game->Bullets.emplace_back(entity->Position.X + 27, entity->Position.Y + 2);
            TimeToFire = FireRate;
        }
    }
}

void GameSystems::SoundSystem(Entity* entity){
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

void GameSystems::PhysicsSystem(Entity* entity){
    if (entity->Active)
    {
        // Move entity?
        if (entity->Velocity) {
            entity->Position.X += entity->Velocity.value()->X * Game->Delta();
            entity->Position.Y += entity->Velocity.value()->Y * Game->Delta();
        }
        // Set new bounding box
        if (entity->Category == CategoryOf::BACKGROUND) 
        {
            // entity->Bounds.w = entity->Sprite.width * entity->Scale.X;
            // entity->Bounds.h = entity->Sprite.height * entity->Scale.Y;
            entity->Bounds.w = Game->Width();
            entity->Bounds.h = Game->Height();
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

void GameSystems::ExpireSystem(Entity* entity){
    if (entity->Active && entity->Expires) {
        auto exp = entity->Expires.value() - Game->Delta();
        entity->Expires = exp;
        if (entity->Expires.value() < 0) {
            entity->Active = false;
        }
    }
}

void GameSystems::TweenSystem(Entity* entity){
    if (entity->Active && entity->Tween) {

        auto x = entity->Scale.X + (entity->Tween.value()->Speed * Game->Delta());
        auto y = entity->Scale.Y + (entity->Tween.value()->Speed * Game->Delta());
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

void GameSystems::RemoveSystem(Entity* entity){
    if (entity->Active) {
        switch(entity->Category) {
            case CategoryOf::ENEMY:
                if (entity->Position.Y > Game->Height()) {
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

double GameSystems::SpawnEnemy(double delta, double t, int enemy) {
    auto d1 = t-delta;
    if (d1 < 0.0) {
        switch(enemy) {
            case 1:
                Game->Enemies1.emplace_back((std::rand() % (Game->Width()-70))+35, 35);
                return 1.0;
            case 2:
                Game->Enemies2.emplace_back((std::rand() % (Game->Width()-170))+85, 85);
                return 4.0;
            case 3:
                Game->Enemies3.emplace_back((std::rand() % (Game->Width()-320))+160, 160);
                return 6.0;
            default:
                return 0;
        }
    } else return d1;    
}

void GameSystems::SpawnSystem(Entity* entity){
    EnemyT1 = SpawnEnemy(Game->Delta(), EnemyT1, 1);
    EnemyT2 = SpawnEnemy(Game->Delta(), EnemyT2, 2);
    EnemyT3 = SpawnEnemy(Game->Delta(), EnemyT3, 3);

}

void GameSystems::EntitySystem(Entity* entity){
    if (!entity->Active) {
        switch(entity->Type) {

            case TypeOf::BULLET: 
                if (Game->Bullets.empty()) break;
                RefreshBullet(entity, Game->Bullets.back().X, Game->Bullets.back().Y);
                Game->Bullets.pop_back();
                break;

            case TypeOf::ENEMY1:
                if (Game->Enemies1.empty()) break;
                RefreshEnemy1(entity, Game->Enemies1.back().X, Game->Enemies1.back().Y);
                Game->Enemies1.pop_back();
                break;

            case TypeOf::ENEMY2:
                if (Game->Enemies2.empty()) break;
                RefreshEnemy2(entity, Game->Enemies2.back().X, Game->Enemies2.back().Y);
                Game->Enemies2.pop_back();
                break;

            case TypeOf::ENEMY3:
                if (Game->Enemies3.empty()) break;
                RefreshEnemy3(entity, Game->Enemies3.back().X, Game->Enemies3.back().Y);
                Game->Enemies3.pop_back();
                break;

            case TypeOf::EXPLOSION:  
                if (Game->Explosions.empty()) break;
                RefreshExplosion(entity, Game->Explosions.back().X, Game->Explosions.back().Y);
                Game->Explosions.pop_back();
                break;

            case TypeOf::BANG:
                if (Game->Bangs.empty()) break;
                RefreshBang(entity, Game->Bangs.back().X, Game->Bangs.back().Y);
                Game->Bangs.pop_back();
                break;

            case TypeOf::PARTICLE:
                if (Game->Particles.empty()) break;
                RefreshParticle(entity, Game->Particles.back().X, Game->Particles.back().Y);
                Game->Particles.pop_back();
                break;

            default:
                break;
        }
    }

}

void GameSystems::HandleCollision(Entity* a, Entity* b){
    Game->Bangs.emplace_back(b->Bounds.x, b->Bounds.y);
    b->Active = false;
    for (int i=0; i<3; i++) Game->Particles.emplace_back(b->Bounds.x, b->Bounds.y);
    if (a->Health) {
        auto h = a->Health.value()->Current - 2;
        if (h < 0) {
            Game->Explosions.emplace_back(a->Position.X, a->Position.Y);
            a->Active = false;
        } else {
            a->Health = new Health(h, a->Health.value()->Maximum);
        }   
    }
}


void GameSystems::CollisionSystem(Entity* entity){
    if (entity->Active && entity->Category == CategoryOf::ENEMY) {
        for (int i=0; i<Game->Entities.size(); i++) {
            auto bullet = &Game->Entities[i];
            if (bullet->Active && bullet->Category == CategoryOf::BULLET) {
                if (SDL_HasIntersection(&entity->Bounds, &bullet->Bounds)) {
                    if (entity->Active && bullet->Active) HandleCollision(entity, bullet);
                    return;
                }
            }
        }
    }
}

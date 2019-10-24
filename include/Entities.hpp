#pragma once
#include "Components.hpp"
#include "xna/Content/ResourceManager.hpp"

static inline void CreateBackground(std::vector<Entity>* entities);
static inline Entity* CreatePlayer(std::vector<Entity>* entities);
static inline void CreateBullet(std::vector<Entity>* entities);
static inline void CreateEnemy1(std::vector<Entity>* entities);
static inline void CreateEnemy2(std::vector<Entity>* entities);
static inline void CreateEnemy3(std::vector<Entity>* entities);
static inline void CreateExplosion(std::vector<Entity>* entities);
static inline void CreateBang(std::vector<Entity>* entities);
static inline void CreateParticle(std::vector<Entity>* entities);


static inline void InitBackground(Entity* entity);
static inline void InitPlayer(Entity* entity);
static inline void InitBullet(Entity* entity);
static inline void InitEnemy1(Entity* entity);
static inline void InitEnemy2(Entity* entity);
static inline void InitEnemy3(Entity* entity);
static inline void InitExplosion(Entity* entity);
static inline void InitBang(Entity* entity);
static inline void InitParticle(Entity* entity);

static inline void RefreshBullet(Entity* entity, int x, int y);
static inline void RefreshEnemy1(Entity* entity, int x, int y);
static inline void RefreshEnemy2(Entity* entity, int x, int y);
static inline void RefreshEnemy3(Entity* entity, int x, int y);
static inline void RefreshExplosion(Entity* entity, int x, int y);
static inline void RefreshBang(Entity* entity, int x, int y);
static inline void RefreshParticle(Entity* entity, int x, int y);

static inline int UniqueId = 0;

/**
 * getResource
 *
 * gets resource from gio resource compiler 
 *
 * @param name
 * @return surface
 */
static inline SDL_Surface* GetResource(std::string name) {
    const std::string path = "assets/images/"+name;
    return IMG_Load(path.c_str());
}

static inline void CreateBackground(std::vector<Entity>* entities){
    entities->emplace_back(UniqueId++, "background", true);
    InitBackground(&entities->back());
}

static inline void InitBackground(Entity* entity) {
    entity->Identity = new Identity(TypeOf::BACKGROUND, CategoryOf::BACKGROUND);
    entity->Transform = new Transform(&xna::ResourceManager::GetTexture("background"), 2.0);
}

static inline Entity* CreatePlayer(std::vector<Entity>* entities) {
    entities->emplace_back(UniqueId++, "player", true);
    InitPlayer(&entities->back());
    return &entities->back();
}

static inline void InitPlayer(Entity* entity) {
    entity->Identity = new Identity(TypeOf::PLAYER, CategoryOf::PLAYER);
    entity->Transform = new Transform(&xna::ResourceManager::GetTexture("spaceshipspr"));
}

static inline void CreateBullet(std::vector<Entity>* entities) {
    entities->emplace_back(UniqueId++, "bullet", false);
    InitBullet(&entities->back());
}
static inline void InitBullet(Entity* entity) {
    entity->Identity = new Identity(TypeOf::BULLET, CategoryOf::BULLET);
    entity->Transform = new Transform(&xna::ResourceManager::GetTexture("bullet"));
}


static inline void RefreshBullet(Entity* entity, int x, int y) {
    entity->Transform.value()->Pos.X = x;
    entity->Transform.value()->Pos.Y = y;
    entity->Expires = new Timer(1.0);
    entity->Sound = new Sound("assets/Sounds/pew.wav");
    entity->Health = new Health(2, 2);
    entity->Tint = new Color(0xd2, 0xfa, 0x00, 0xffa);
    entity->Velocity = new Vector2D(0, -800);
    entity->Active = true;
}

static inline void CreateEnemy1(std::vector<Entity>* entities){
    entities->emplace_back(UniqueId++, "enemy1", false);
    InitEnemy1(&entities->back());
}
static inline void InitEnemy1(Entity* entity) {
    entity->Identity = new Identity(TypeOf::ENEMY1, CategoryOf::ENEMY);
    entity->Transform = new Transform(&xna::ResourceManager::GetTexture("enemy1"));
}
static inline void RefreshEnemy1(Entity* entity, int x, int y) {
    entity->Transform.value()->Pos.X = x;
    entity->Transform.value()->Pos.Y = y;
    entity->Health = new Health(10, 10);
    entity->Velocity = new Vector2D(0, 40);
    entity->Active = true;
}

static inline void CreateEnemy2(std::vector<Entity>* entities){
    entities->emplace_back(UniqueId++, "enemy2", false);
    InitEnemy2(&entities->back());
}
static inline void InitEnemy2(Entity* entity) {
    entity->Identity = new Identity(TypeOf::ENEMY2, CategoryOf::ENEMY);
    entity->Transform = new Transform(&xna::ResourceManager::GetTexture("enemy2"));
}
static inline void RefreshEnemy2(Entity* entity, int x, int y){
    entity->Transform.value()->Pos.X = x;
    entity->Transform.value()->Pos.Y = y;
    entity->Health = new Health(20, 20);
    entity->Velocity = new Vector2D(0, 30);
    entity->Active = true;
}
static inline void CreateEnemy3(std::vector<Entity>* entities){
    entities->emplace_back(UniqueId++, "enemy3", false);
    InitEnemy3(&entities->back());
}
static inline void InitEnemy3(Entity* entity) {
    entity->Identity = new Identity(TypeOf::ENEMY3, CategoryOf::ENEMY);
    entity->Transform = new Transform(&xna::ResourceManager::GetTexture("enemy3"));
}
static inline void RefreshEnemy3(Entity* entity, int x, int y){
    entity->Transform.value()->Pos.X = x;
    entity->Transform.value()->Pos.Y = y;
    entity->Health = new Health(60, 60);
    entity->Velocity = new Vector2D(0, 20);
    entity->Active = true;
}

static inline void CreateExplosion(std::vector<Entity>* entities){
    entities->emplace_back(UniqueId++, "explosion", false);
    InitExplosion(&entities->back());
}
static inline void InitExplosion(Entity* entity) {
    entity->Identity = new Identity(TypeOf::EXPLOSION, CategoryOf::EXPLOSION);
    entity->Transform = new Transform(&xna::ResourceManager::GetTexture("explosion"), 0.6);
}

static inline void RefreshExplosion(Entity* entity, int x, int y){
    auto scale = 0.6;
    entity->Transform.value()->Pos.X = x;
    entity->Transform.value()->Pos.Y = y;
    entity->Transform.value()->Bounds.x = x; 
    entity->Transform.value()->Bounds.y = y; 
    entity->Transform.value()->Scale.X = scale;
    entity->Transform.value()->Scale.Y = scale;
    entity->Sound = new Sound("assets/Sounds/asplode.wav");
    entity->Tween = new Tween(scale/100.0, scale, -3, false, true);
    entity->Tint = new Color(0xd2, 0xfa, 0xd2, 0xfa);
    entity->Expires = new Timer(0.2);
    entity->Active = true;
}
static inline void CreateBang(std::vector<Entity>* entities){
    entities->emplace_back(UniqueId++, "bang", false);
    InitBang(&entities->back());
}
static inline void InitBang(Entity* entity) {
    entity->Identity = new Identity(TypeOf::BANG, CategoryOf::EXPLOSION);
    entity->Transform = new Transform(&xna::ResourceManager::GetTexture("explosion"), 0.4);
}
static inline void RefreshBang(Entity* entity, int x, int y){
    auto scale = 0.4;
    entity->Transform.value()->Pos.X = x;
    entity->Transform.value()->Pos.Y = y;
    entity->Transform.value()->Bounds.x = x; 
    entity->Transform.value()->Bounds.y = y; 
    entity->Transform.value()->Scale.X = scale;
    entity->Transform.value()->Scale.Y = scale;
    entity->Sound = new Sound("assets/Sounds/smallasplode.wav");
    entity->Tween = new Tween(scale/100.0, scale, -3, false, true);
    entity->Tint = new Color(0xd2, 0xfa, 0xd2, 0xfa);
    entity->Expires = new Timer(0.2);
    entity->Active = true;
}
static inline void CreateParticle(std::vector<Entity>* entities){
    entities->emplace_back(UniqueId++, "particle", false);
    InitParticle(&entities->back());
}
static inline void InitParticle(Entity* entity) {
    entity->Identity = new Identity(TypeOf::PARTICLE, CategoryOf::PARTICLE);
    entity->Transform = new Transform(&xna::ResourceManager::GetTexture("star"));
}

static inline void RefreshParticle(Entity* entity, int x, int y){
    auto Tau = 6.28318;
    double r1 = ((double)std::rand()/(double)1.0);
    double radians = r1 * (double)Tau;
    double magnitude = std::rand() % 100 + 50;
    double velocityX = magnitude * cos(radians);
    double velocityY = magnitude * sin(radians);
    double scale = (double)(std::rand() % 10) / 10.0;

    entity->Transform.value()->Pos.X = x;
    entity->Transform.value()->Pos.Y = y;
    entity->Transform.value()->Bounds.x = x; 
    entity->Transform.value()->Bounds.y = y; 
    entity->Transform.value()->Scale.X = scale;
    entity->Transform.value()->Scale.Y = scale;
    entity->Velocity = new Vector2D(velocityX, velocityY);
    entity->Tint = new Color(0xfa, 0xfa, 0xd2, 0xff);
    entity->Expires = new Timer(0.75);
    entity->Active = true;
}


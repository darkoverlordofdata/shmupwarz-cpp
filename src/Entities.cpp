/** 
 * Entity FTypey
 */
#include "Entities.h"

int UniqueId = 0;

/**
 * getResource
 *
 * gets resource from gio resource compiler 
 *
 * @param name
 * @return surface
 */
SDL_Surface* GetResource(std::string name) {
    const std::string path = "assets/images/"+name;
    return IMG_Load(path.c_str());
}

void CreateBackground(std::vector<Entity>* entities){
    entities->emplace_back(UniqueId++, "background", true);
    InitBackground(&entities->back());
}

void InitBackground(Entity* entity) {
    const auto scale = 2.0;
    entity->Type = TypeOf::BACKGROUND;
    entity->Category = CategoryOf::BACKGROUND;
    entity->Sprite.Texture = xna::ResourceManager::GetTexture("background");
    entity->Sprite.Width = entity->Sprite.Texture.Width*scale;
    entity->Sprite.Height = entity->Sprite.Texture.Height*scale;
    

    entity->Bounds.w = entity->Sprite.Texture.Width*scale; 
    entity->Bounds.h = entity->Sprite.Texture.Height*scale; 
    entity->Scale.X = scale;
    entity->Scale.Y = scale;
    // SDL_FreeSurface(surface);
}

Entity* CreatePlayer(std::vector<Entity>* entities) {
    entities->emplace_back(UniqueId++, "player", true);
    InitPlayer(&entities->back());
    return &entities->back();
}

void InitPlayer(Entity* entity) {
    auto scale = 1.0;
    entity->Type = TypeOf::PLAYER;
    entity->Category = CategoryOf::PLAYER;
    entity->Sprite.Texture = xna::ResourceManager::GetTexture("spaceshipspr");
    entity->Sprite.Width = entity->Sprite.Texture.Width*scale;
    entity->Sprite.Height = entity->Sprite.Texture.Height*scale;
    entity->Bounds.w = entity->Sprite.Texture.Width*scale; 
    entity->Bounds.h = entity->Sprite.Texture.Height*scale; 
    entity->Scale.X = scale;
    entity->Scale.Y = scale;
    // SDL_FreeSurface(surface);
}

void CreateBullet(std::vector<Entity>* entities) {
    entities->emplace_back(UniqueId++, "bullet", false);
    InitBullet(&entities->back());
}
void InitBullet(Entity* entity) {
    auto scale = 1.0;
    entity->Type = TypeOf::BULLET;
    entity->Category = CategoryOf::BULLET;
    entity->Sprite.Texture = xna::ResourceManager::GetTexture("bullet");
    entity->Sprite.Width = entity->Sprite.Texture.Width*scale;
    entity->Sprite.Height = entity->Sprite.Texture.Height*scale;
    entity->Bounds.w = entity->Sprite.Texture.Width*scale; 
    entity->Bounds.h = entity->Sprite.Texture.Height*scale; 
    entity->Scale.X = scale;
    entity->Scale.Y = scale;
    // SDL_FreeSurface(surface);
}

void RefreshBullet(Entity* entity, int x, int y) {
    entity->Position.X = x;
    entity->Position.Y = y;
    entity->Expires = 1.0;
    entity->Sound = Effect::PEW;
    entity->Health = new Health(2, 2);
    entity->Tint = new Color(0xd2, 0xfa, 0x00, 0xffa);
    entity->Velocity = new Vector2d(0, -800);
    entity->Active = true;
}

void CreateEnemy1(std::vector<Entity>* entities){
    entities->emplace_back(UniqueId++, "enemy1", false);
    InitEnemy1(&entities->back());
}
void InitEnemy1(Entity* entity) {
    auto scale = 1.0;
    entity->Type = TypeOf::ENEMY1;
    entity->Category = CategoryOf::ENEMY;
    entity->Sprite.Texture = xna::ResourceManager::GetTexture("enemy1");
    entity->Sprite.Width = entity->Sprite.Texture.Width*scale;
    entity->Sprite.Height = entity->Sprite.Texture.Height*scale;
    entity->Bounds.w = entity->Sprite.Texture.Width*scale; 
    entity->Bounds.h = entity->Sprite.Texture.Height*scale; 
    entity->Scale.X = scale;
    entity->Scale.Y = scale;
    // SDL_FreeSurface(surface);
}
void RefreshEnemy1(Entity* entity, int x, int y) {
    entity->Position.X = x;
    entity->Position.Y = y;
    entity->Health = new Health(10, 10);
    entity->Velocity = new Vector2d(0, 40);
    entity->Active = true;
}

void CreateEnemy2(std::vector<Entity>* entities){
    entities->emplace_back(UniqueId++, "enemy2", false);
    InitEnemy2(&entities->back());
}
void InitEnemy2(Entity* entity) {
    auto scale = 1.0;
    entity->Type = TypeOf::ENEMY2;
    entity->Category = CategoryOf::ENEMY;
    entity->Sprite.Texture = xna::ResourceManager::GetTexture("enemy2");
    entity->Sprite.Width = entity->Sprite.Texture.Width*scale;
    entity->Sprite.Height = entity->Sprite.Texture.Height*scale;
    entity->Bounds.w = entity->Sprite.Texture.Width*scale; 
    entity->Bounds.h = entity->Sprite.Texture.Height*scale; 
    entity->Scale.X = scale;
    entity->Scale.Y = scale;
    // SDL_FreeSurface(surface);
}
void RefreshEnemy2(Entity* entity, int x, int y){
    entity->Position.X = x;
    entity->Position.Y = y;
    entity->Health = new Health(20, 20);
    entity->Velocity = new Vector2d(0, 30);
    entity->Active = true;
}
void CreateEnemy3(std::vector<Entity>* entities){
    entities->emplace_back(UniqueId++, "enemy3", false);
    InitEnemy3(&entities->back());
}
void InitEnemy3(Entity* entity) {
    auto scale = 1.0;
    entity->Type = TypeOf::ENEMY3;
    entity->Category = CategoryOf::ENEMY;
    entity->Sprite.Texture = xna::ResourceManager::GetTexture("enemy3");
    entity->Sprite.Width = entity->Sprite.Texture.Width*scale;
    entity->Sprite.Height = entity->Sprite.Texture.Height*scale;
    entity->Bounds.w = entity->Sprite.Texture.Width*scale; 
    entity->Bounds.h = entity->Sprite.Texture.Height*scale; 
    entity->Scale.X = scale;
    entity->Scale.Y = scale;
    // SDL_FreeSurface(surface);
}
void RefreshEnemy3(Entity* entity, int x, int y){
    entity->Position.X = x;
    entity->Position.Y = y;
    entity->Health = new Health(60, 60);
    entity->Velocity = new Vector2d(0, 20);
    entity->Active = true;
}

void CreateExplosion(std::vector<Entity>* entities){
    entities->emplace_back(UniqueId++, "explosion", false);
    InitExplosion(&entities->back());
}
void InitExplosion(Entity* entity) {
    auto scale = 0.6;
    entity->Type = TypeOf::EXPLOSION;
    entity->Category = CategoryOf::EXPLOSION;
    entity->Sprite.Texture = xna::ResourceManager::GetTexture("explosion");
    entity->Sprite.Width = entity->Sprite.Texture.Width*scale;
    entity->Sprite.Height = entity->Sprite.Texture.Height*scale;
    entity->Bounds.w = entity->Sprite.Texture.Width*scale; 
    entity->Bounds.h = entity->Sprite.Texture.Height*scale; 
    entity->Scale.X = scale;
    entity->Scale.Y = scale;
    // SDL_FreeSurface(surface);
}
void RefreshExplosion(Entity* entity, int x, int y){
    auto scale = 0.6;
    entity->Position.X = x;
    entity->Position.Y = y;
    entity->Bounds.x = x; 
    entity->Bounds.y = y; 
    entity->Scale.X = scale;
    entity->Scale.Y = scale;
    entity->Sound = Effect::ASPLODE;
    entity->Tween = new Tween(scale/100.0, scale, -3, false, true);
    entity->Tint = new Color(0xd2, 0xfa, 0xd2, 0xfa);
    entity->Expires = 0.2;
    entity->Active = true;
}
void CreateBang(std::vector<Entity>* entities){
    entities->emplace_back(UniqueId++, "bang", false);
    InitBang(&entities->back());
}
void InitBang(Entity* entity) {
    auto scale = 0.4;
    entity->Type = TypeOf::BANG;
    entity->Category = CategoryOf::EXPLOSION;
    entity->Sprite.Texture = xna::ResourceManager::GetTexture("explosion");
    entity->Sprite.Width = entity->Sprite.Texture.Width*scale;
    entity->Sprite.Height = entity->Sprite.Texture.Height*scale;
    entity->Bounds.w = entity->Sprite.Texture.Width*scale; 
    entity->Bounds.h = entity->Sprite.Texture.Height*scale; 
    entity->Scale.X = scale;
    entity->Scale.Y = scale;
    // SDL_FreeSurface(surface);
}
void RefreshBang(Entity* entity, int x, int y){
    auto scale = 0.4;
    entity->Position.X = x;
    entity->Position.Y = y;
    entity->Bounds.x = x; 
    entity->Bounds.y = y; 
    entity->Scale.X = scale;
    entity->Scale.Y = scale;
    entity->Sound = Effect::SMALLASPLODE;
    entity->Tween = new Tween(scale/100.0, scale, -3, false, true);
    entity->Tint = new Color(0xd2, 0xfa, 0xd2, 0xfa);
    entity->Expires = 0.2;
    entity->Active = true;
}
void CreateParticle(std::vector<Entity>* entities){
    entities->emplace_back(UniqueId++, "particle", false);
    InitParticle(&entities->back());
}
void InitParticle(Entity* entity) {
    auto scale = 1.0;
    entity->Type = TypeOf::PARTICLE;
    entity->Category = CategoryOf::PARTICLE;
    entity->Sprite.Texture = xna::ResourceManager::GetTexture("star");
    entity->Sprite.Width = entity->Sprite.Texture.Width*scale;
    entity->Sprite.Height = entity->Sprite.Texture.Height*scale;
    entity->Bounds.w = entity->Sprite.Texture.Width*scale; 
    entity->Bounds.h = entity->Sprite.Texture.Height*scale; 
    entity->Scale.X = scale;
    entity->Scale.Y = scale;
    // SDL_FreeSurface(surface);
}

// var radians:number = Math.random()*Tau
// var magnitude:number = MathUtils.random(200)
// var velocityX = magnitude * Math.cos(radians)
// var velocityY = magnitude * Math.sin(radians)

void RefreshParticle(Entity* entity, int x, int y){
    auto Tau = 6.28318;
    // auto radians = ((double)std::rand()/1.0) * Tau;
    // auto magnitude = std::rand() % 100 + 50;
    // auto velocityX = magnitude * cos(radians);
    // auto velocityY = magnitude * sin(radians);
    auto radians = ((double)std::rand()/(double)1.0) * (double)Tau;
    auto magnitude = std::rand() % 100 + 50;
    auto velocityX = magnitude * cos(radians);
    auto velocityY = magnitude * sin(radians);
    auto scale = (double)(std::rand() % 10) / 10.0;
    // std::cout << velocityX << ", " << velocityY << "\n" << std::flush;
    entity->Position.X = x;
    entity->Position.Y = y;
    entity->Bounds.x = x; 
    entity->Bounds.y = y; 
    entity->Scale.X = scale;
    entity->Scale.Y = scale;
    entity->Velocity = new Vector2d(velocityX, velocityY);
    entity->Tint = new Color(0xfa, 0xfa, 0xd2, 0xff);
    entity->Expires = 0.75;
    entity->Active = true;
}


/** 
 * Entity Factory
 */
#include "entities.h"
#include "resource_manager.h"

int uniqueId = 0;

/**
 * getResource
 *
 * gets resource from gio resource compiler 
 *
 * @param name
 * @return surface
 */
SDL_Surface* getResource(std::string name) {
    const std::string path = "assets/images/"+name;
    return IMG_Load(path.c_str());
}

void createBackground(std::vector<Entity>* entities){
    entities->emplace_back(uniqueId++, "background", true);
    initBackground(&entities->back());
}

void initBackground(Entity* entity) {
    const auto scale = 2.0;
    entity->actor = Actor::BACKGROUND;
    entity->category = Category::BACKGROUND;
    entity->sprite.texture = ResourceManager::GetTexture("background");
    entity->sprite.width = entity->sprite.texture.Width*scale;
    entity->sprite.height = entity->sprite.texture.Height*scale;
    

    entity->bounds.w = entity->sprite.texture.Width*scale; 
    entity->bounds.h = entity->sprite.texture.Height*scale; 
    entity->scale.x = scale;
    entity->scale.y = scale;
    // SDL_FreeSurface(surface);
}

Entity* createPlayer(std::vector<Entity>* entities) {
    entities->emplace_back(uniqueId++, "player", true);
    initPlayer(&entities->back());
    return &entities->back();
}

void initPlayer(Entity* entity) {
    auto scale = 1.0;
    entity->actor = Actor::PLAYER;
    entity->category = Category::PLAYER;
    entity->sprite.texture = ResourceManager::GetTexture("spaceshipspr");
    entity->sprite.width = entity->sprite.texture.Width*scale;
    entity->sprite.height = entity->sprite.texture.Height*scale;
    entity->bounds.w = entity->sprite.texture.Width*scale; 
    entity->bounds.h = entity->sprite.texture.Height*scale; 
    entity->scale.x = scale;
    entity->scale.y = scale;
    // SDL_FreeSurface(surface);
}

void createBullet(std::vector<Entity>* entities) {
    entities->emplace_back(uniqueId++, "bullet", false);
    initBullet(&entities->back());
}
void initBullet(Entity* entity) {
    auto scale = 1.0;
    entity->actor = Actor::BULLET;
    entity->category = Category::BULLET;
    entity->sprite.texture = ResourceManager::GetTexture("bullet");
    entity->sprite.width = entity->sprite.texture.Width*scale;
    entity->sprite.height = entity->sprite.texture.Height*scale;
    entity->bounds.w = entity->sprite.texture.Width*scale; 
    entity->bounds.h = entity->sprite.texture.Height*scale; 
    entity->scale.x = scale;
    entity->scale.y = scale;
    // SDL_FreeSurface(surface);
}

void refreshBullet(Entity* entity, int x, int y) {
    entity->position.x = x;
    entity->position.y = y;
    entity->expires = 1.0;
    entity->sound = Effect::PEW;
    entity->health = new Health(2, 2);
    entity->tint = new Color(0xd2, 0xfa, 0x00, 0xffa);
    entity->velocity = new Vector2d(0, -800);
    entity->active = true;
}

void createEnemy1(std::vector<Entity>* entities){
    entities->emplace_back(uniqueId++, "enemy1", false);
    initEnemy1(&entities->back());
}
void initEnemy1(Entity* entity) {
    auto scale = 1.0;
    entity->actor = Actor::ENEMY1;
    entity->category = Category::ENEMY;
    entity->sprite.texture = ResourceManager::GetTexture("enemy1");
    entity->sprite.width = entity->sprite.texture.Width*scale;
    entity->sprite.height = entity->sprite.texture.Height*scale;
    entity->bounds.w = entity->sprite.texture.Width*scale; 
    entity->bounds.h = entity->sprite.texture.Height*scale; 
    entity->scale.x = scale;
    entity->scale.y = scale;
    // SDL_FreeSurface(surface);
}
void refreshEnemy1(Entity* entity, int x, int y) {
    entity->position.x = x;
    entity->position.y = y;
    entity->health = new Health(10, 10);
    entity->velocity = new Vector2d(0, 40);
    entity->active = true;
}

void createEnemy2(std::vector<Entity>* entities){
    entities->emplace_back(uniqueId++, "enemy2", false);
    initEnemy2(&entities->back());
}
void initEnemy2(Entity* entity) {
    auto scale = 1.0;
    entity->actor = Actor::ENEMY2;
    entity->category = Category::ENEMY;
    entity->sprite.texture = ResourceManager::GetTexture("enemy2");
    entity->sprite.width = entity->sprite.texture.Width*scale;
    entity->sprite.height = entity->sprite.texture.Height*scale;
    entity->bounds.w = entity->sprite.texture.Width*scale; 
    entity->bounds.h = entity->sprite.texture.Height*scale; 
    entity->scale.x = scale;
    entity->scale.y = scale;
    // SDL_FreeSurface(surface);
}
void refreshEnemy2(Entity* entity, int x, int y){
    entity->position.x = x;
    entity->position.y = y;
    entity->health = new Health(20, 20);
    entity->velocity = new Vector2d(0, 30);
    entity->active = true;
}
void createEnemy3(std::vector<Entity>* entities){
    entities->emplace_back(uniqueId++, "enemy3", false);
    initEnemy3(&entities->back());
}
void initEnemy3(Entity* entity) {
    auto scale = 1.0;
    entity->actor = Actor::ENEMY3;
    entity->category = Category::ENEMY;
    entity->sprite.texture = ResourceManager::GetTexture("enemy3");
    entity->sprite.width = entity->sprite.texture.Width*scale;
    entity->sprite.height = entity->sprite.texture.Height*scale;
    entity->bounds.w = entity->sprite.texture.Width*scale; 
    entity->bounds.h = entity->sprite.texture.Height*scale; 
    entity->scale.x = scale;
    entity->scale.y = scale;
    // SDL_FreeSurface(surface);
}
void refreshEnemy3(Entity* entity, int x, int y){
    entity->position.x = x;
    entity->position.y = y;
    entity->health = new Health(60, 60);
    entity->velocity = new Vector2d(0, 20);
    entity->active = true;
}

void createExplosion(std::vector<Entity>* entities){
    entities->emplace_back(uniqueId++, "explosion", false);
    initExplosion(&entities->back());
}
void initExplosion(Entity* entity) {
    auto scale = 0.6;
    entity->actor = Actor::EXPLOSION;
    entity->category = Category::EXPLOSION;
    entity->sprite.texture = ResourceManager::GetTexture("explosion");
    entity->sprite.width = entity->sprite.texture.Width*scale;
    entity->sprite.height = entity->sprite.texture.Height*scale;
    entity->bounds.w = entity->sprite.texture.Width*scale; 
    entity->bounds.h = entity->sprite.texture.Height*scale; 
    entity->scale.x = scale;
    entity->scale.y = scale;
    // SDL_FreeSurface(surface);
}
void refreshExplosion(Entity* entity, int x, int y){
    auto scale = 0.6;
    entity->position.x = x;
    entity->position.y = y;
    entity->bounds.x = x; 
    entity->bounds.y = y; 
    entity->scale.x = scale;
    entity->scale.y = scale;
    entity->sound = Effect::ASPLODE;
    entity->tween = new Tween(scale/100.0, scale, -3, false, true);
    entity->tint = new Color(0xd2, 0xfa, 0xd2, 0xfa);
    entity->expires = 0.2;
    entity->active = true;
}
void createBang(std::vector<Entity>* entities){
    entities->emplace_back(uniqueId++, "bang", false);
    initBang(&entities->back());
}
void initBang(Entity* entity) {
    auto scale = 0.4;
    entity->actor = Actor::BANG;
    entity->category = Category::EXPLOSION;
    entity->sprite.texture = ResourceManager::GetTexture("explosion");
    entity->sprite.width = entity->sprite.texture.Width*scale;
    entity->sprite.height = entity->sprite.texture.Height*scale;
    entity->bounds.w = entity->sprite.texture.Width*scale; 
    entity->bounds.h = entity->sprite.texture.Height*scale; 
    entity->scale.x = scale;
    entity->scale.y = scale;
    // SDL_FreeSurface(surface);
}
void refreshBang(Entity* entity, int x, int y){
    auto scale = 0.4;
    entity->position.x = x;
    entity->position.y = y;
    entity->bounds.x = x; 
    entity->bounds.y = y; 
    entity->scale.x = scale;
    entity->scale.y = scale;
    entity->sound = Effect::SMALLASPLODE;
    entity->tween = new Tween(scale/100.0, scale, -3, false, true);
    entity->tint = new Color(0xd2, 0xfa, 0xd2, 0xfa);
    entity->expires = 0.2;
    entity->active = true;
}
void createParticle(std::vector<Entity>* entities){
    entities->emplace_back(uniqueId++, "particle", false);
    initParticle(&entities->back());
}
void initParticle(Entity* entity) {
    auto scale = 1.0;
    entity->actor = Actor::PARTICLE;
    entity->category = Category::PARTICLE;
    entity->sprite.texture = ResourceManager::GetTexture("star");
    entity->sprite.width = entity->sprite.texture.Width*scale;
    entity->sprite.height = entity->sprite.texture.Height*scale;
    entity->bounds.w = entity->sprite.texture.Width*scale; 
    entity->bounds.h = entity->sprite.texture.Height*scale; 
    entity->scale.x = scale;
    entity->scale.y = scale;
    // SDL_FreeSurface(surface);
}

// var radians:number = Math.random()*Tau
// var magnitude:number = MathUtils.random(200)
// var velocityX = magnitude * Math.cos(radians)
// var velocityY = magnitude * Math.sin(radians)

void refreshParticle(Entity* entity, int x, int y){
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
    entity->position.x = x;
    entity->position.y = y;
    entity->bounds.x = x; 
    entity->bounds.y = y; 
    entity->scale.x = scale;
    entity->scale.y = scale;
    entity->velocity = new Vector2d(velocityX, velocityY);
    entity->tint = new Color(0xfa, 0xfa, 0xd2, 0xff);
    entity->expires = 0.75;
    entity->active = true;
}


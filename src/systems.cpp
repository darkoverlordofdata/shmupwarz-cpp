#include "systems.h"
#include "demo.h"


Systems::Systems(Demo* g): demo(g) {
    pew = Mix_LoadWAV("assets/sounds/pew.wav");
    asplode = Mix_LoadWAV("assets/sounds/asplode.wav");
    smallasplode = Mix_LoadWAV("assets/sounds/smallasplode.wav");
}
Systems::~Systems(){}

void Systems::inputSystem(Entity* entity){
    entity->position.x = demo->mouseX;
    entity->position.y = demo->mouseY;
    if (demo->getKey(122) || demo->mouseDown) {
        timeToFire -= demo->delta;
        if (timeToFire < 0.0) {
            demo->bullets.emplace_back(entity->position.x - 27, entity->position.y + 2);
            demo->bullets.emplace_back(entity->position.x + 27, entity->position.y + 2);
            timeToFire = FireRate;
        }
    }
}

void Systems::soundSystem(Entity* entity){
    if (entity->active && entity->sound) {
        switch(entity->sound.value()) {
            case Effect::PEW: 
                Mix_PlayChannelTimed(-1, pew, 0, 0);
                break;

            case Effect::ASPLODE: 
                Mix_PlayChannelTimed(-1, asplode, 0, 0);
                break;

            case Effect::SMALLASPLODE: 
                Mix_PlayChannelTimed(-1, smallasplode, 0, 0);
                break;
        }
    }
}

void Systems::physicsSystem(Entity* entity){
    if (entity->active)
    {
        // Move entity?
        if (entity->velocity) {
            entity->position.x += entity->velocity.value()->x * demo->delta;
            entity->position.y += entity->velocity.value()->y * demo->delta;
        }
        // Set new bounding box
        if (entity->category == Category::BACKGROUND) 
        {
            // entity->bounds.w = entity->sprite.width * entity->scale.x;
            // entity->bounds.h = entity->sprite.height * entity->scale.y;
            entity->bounds.w = demo->width;
            entity->bounds.h = demo->height;
            entity->bounds.x = 0; 
            entity->bounds.y = 0; 
        } else {
            entity->bounds.w = entity->sprite.width * entity->scale.x;
            entity->bounds.h = entity->sprite.height * entity->scale.y;
            entity->bounds.x = entity->position.x - entity->bounds.w / 2;
            entity->bounds.y = entity->position.y - entity->bounds.h / 2;
        }
    }
}

void Systems::expireSystem(Entity* entity){
    if (entity->active && entity->expires) {
        auto exp = entity->expires.value() - demo->delta;
        entity->expires = exp;
        if (entity->expires.value() < 0) {
            entity->active = false;
        }
    }
}

void Systems::tweenSystem(Entity* entity){
    if (entity->active && entity->tween) {

        auto x = entity->scale.x + (entity->tween.value()->speed * demo->delta);
        auto y = entity->scale.y + (entity->tween.value()->speed * demo->delta);
        auto active = entity->tween.value()->active;


        if (x > entity->tween.value()->max) {
            x = entity->tween.value()->max;
            y = entity->tween.value()->max;
            active = false;
        } else if (x < entity->tween.value()->min) {
            x = entity->tween.value()->min;
            y = entity->tween.value()->min;
            active = false;
        }
        entity->scale.x = x; 
        entity->scale.y = y; 
        entity->tween = new Tween(entity->tween.value()->min, 
                                    entity->tween.value()->max, 
                                    entity->tween.value()->speed, 
                                    entity->tween.value()->repeat, active);
    }
}

void Systems::removeSystem(Entity* entity){
    if (entity->active) {
        switch(entity->category) {
            case Category::ENEMY:
                if (entity->position.y > demo->height) {
                    entity->active = false;
                }
                break;
            case Category::BULLET:
                if (entity->position.y < 0) {
                    entity->active = false;
                }
                break;
            default:
                break;
        }
    }
}

double Systems::spawnEnemy(double delta, double t, int enemy) {
    auto d1 = t-delta;
    if (d1 < 0.0) {
        switch(enemy) {
            case 1:
                demo->enemies1.emplace_back((std::rand() % (demo->width-70))+35, 35);
                return 1.0;
            case 2:
                demo->enemies2.emplace_back((std::rand() % (demo->width-170))+85, 85);
                return 4.0;
            case 3:
                demo->enemies3.emplace_back((std::rand() % (demo->width-320))+160, 160);
                return 6.0;
            default:
                return 0;
        }
    } else return d1;    
}

void Systems::spawnSystem(Entity* entity){
    enemyT1 = spawnEnemy(demo->delta, enemyT1, 1);
    enemyT2 = spawnEnemy(demo->delta, enemyT2, 2);
    enemyT3 = spawnEnemy(demo->delta, enemyT3, 3);

}

void Systems::entitySystem(Entity* entity){
    if (!entity->active) {
        switch(entity->actor) {

            case Actor::BULLET: 
                if (demo->bullets.empty()) break;
                refreshBullet(entity, demo->bullets.back().x, demo->bullets.back().y);
                demo->bullets.pop_back();
                break;

            case Actor::ENEMY1:
                if (demo->enemies1.empty()) break;
                refreshEnemy1(entity, demo->enemies1.back().x, demo->enemies1.back().y);
                demo->enemies1.pop_back();
                break;

            case Actor::ENEMY2:
                if (demo->enemies2.empty()) break;
                refreshEnemy2(entity, demo->enemies2.back().x, demo->enemies2.back().y);
                demo->enemies2.pop_back();
                break;

            case Actor::ENEMY3:
                if (demo->enemies3.empty()) break;
                refreshEnemy3(entity, demo->enemies3.back().x, demo->enemies3.back().y);
                demo->enemies3.pop_back();
                break;

            case Actor::EXPLOSION:  
                if (demo->explosions.empty()) break;
                refreshExplosion(entity, demo->explosions.back().x, demo->explosions.back().y);
                demo->explosions.pop_back();
                break;

            case Actor::BANG:
                if (demo->bangs.empty()) break;
                refreshBang(entity, demo->bangs.back().x, demo->bangs.back().y);
                demo->bangs.pop_back();
                break;

            case Actor::PARTICLE:
                if (demo->particles.empty()) break;
                refreshParticle(entity, demo->particles.back().x, demo->particles.back().y);
                demo->particles.pop_back();
                break;

            default:
                break;
        }
    }

}

void Systems::handleCollision(Entity* a, Entity* b){
    demo->bangs.emplace_back(b->bounds.x, b->bounds.y);
    b->active = false;
    for (int i=0; i<3; i++) demo->particles.emplace_back(b->bounds.x, b->bounds.y);
    if (a->health) {
        auto h = a->health.value()->current - 2;
        if (h < 0) {
            demo->explosions.emplace_back(a->position.x, a->position.y);
            a->active = false;
        } else {
            a->health = new Health(h, a->health.value()->maximum);
        }   
    }
}

// bool Systems::intersects(SDL_Rect* r1, SDL_Rect* r2) {
//     return ((r1->x < r2->x + r2->w) && 
//             (r1->x + r1->w > r2->x) && 
//             (r1->y < r2->y + r2->h) && 
//             (r1->y + r1->h > r2->y));
// }

void Systems::collisionSystem(Entity* entity){
    if (entity->active && entity->category == Category::ENEMY) {
        for (int i=0; i<demo->entities.size(); i++) {
            auto bullet = &demo->entities[i];
            if (bullet->active && bullet->category == Category::BULLET) {
                if (SDL_HasIntersection(&entity->bounds, &bullet->bounds)) {
                    if (entity->active && bullet->active) handleCollision(entity, bullet);
                    return;
                }
            }
        }
    }
}

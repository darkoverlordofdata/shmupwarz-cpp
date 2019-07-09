#pragma once
#include "Components.h"
#include "ResourceManager.h"

void createBackground(std::vector<Entity>* entities);
Entity* createPlayer(std::vector<Entity>* entities);
void createBullet(std::vector<Entity>* entities);
void createEnemy1(std::vector<Entity>* entities);
void createEnemy2(std::vector<Entity>* entities);
void createEnemy3(std::vector<Entity>* entities);
void createExplosion(std::vector<Entity>* entities);
void createBang(std::vector<Entity>* entities);
void createParticle(std::vector<Entity>* entities);


void initBackground(Entity* entity);
void initPlayer(Entity* entity);
void initBullet(Entity* entity);
void initEnemy1(Entity* entity);
void initEnemy2(Entity* entity);
void initEnemy3(Entity* entity);
void initExplosion(Entity* entity);
void initBang(Entity* entity);
void initParticle(Entity* entity);

void refreshBullet(Entity* entity, int x, int y);
void refreshEnemy1(Entity* entity, int x, int y);
void refreshEnemy2(Entity* entity, int x, int y);
void refreshEnemy3(Entity* entity, int x, int y);
void refreshExplosion(Entity* entity, int x, int y);
void refreshBang(Entity* entity, int x, int y);
void refreshParticle(Entity* entity, int x, int y);


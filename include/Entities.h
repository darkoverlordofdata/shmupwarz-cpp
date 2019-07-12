#pragma once
#include "Components.h"
#include "xna/Content/ResourceManager.h"

void CreateBackground(std::vector<Entity>* entities);
Entity* CreatePlayer(std::vector<Entity>* entities);
void CreateBullet(std::vector<Entity>* entities);
void CreateEnemy1(std::vector<Entity>* entities);
void CreateEnemy2(std::vector<Entity>* entities);
void CreateEnemy3(std::vector<Entity>* entities);
void CreateExplosion(std::vector<Entity>* entities);
void CreateBang(std::vector<Entity>* entities);
void CreateParticle(std::vector<Entity>* entities);


void InitBackground(Entity* entity);
void InitPlayer(Entity* entity);
void InitBullet(Entity* entity);
void InitEnemy1(Entity* entity);
void InitEnemy2(Entity* entity);
void InitEnemy3(Entity* entity);
void InitExplosion(Entity* entity);
void InitBang(Entity* entity);
void InitParticle(Entity* entity);

void RefreshBullet(Entity* entity, int x, int y);
void RefreshEnemy1(Entity* entity, int x, int y);
void RefreshEnemy2(Entity* entity, int x, int y);
void RefreshEnemy3(Entity* entity, int x, int y);
void RefreshExplosion(Entity* entity, int x, int y);
void RefreshBang(Entity* entity, int x, int y);
void RefreshParticle(Entity* entity, int x, int y);


#pragma once
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <list>
#include <vector>
#include <cstdio>
#include <map>
#include <string>
#include <iostream>
#include <ctime>
#include <chrono>
#include <list>
#include <algorithm>
#include <random>
#include <chrono>
#include "Components.h"
#include "Entities.h"
#include "Systems.h"
#include "Texture2D.h"
#include "Shader.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "xna/Game.h"

enum {
    DISPLAY_WIDTH  = 480,
    DISPLAY_HEIGHT = 320,
    UPDATE_INTERVAL = 1000/60,
    HERO_SPEED = 2
};

class Systems;
    
class Shmupwarz : public xna::Game {
friend class Systems;
public:
    Shmupwarz(std::string title, int width, int height, SDL_Window* window);
    ~Shmupwarz();
    void draw() override;
    void update() override;
    void init() override;
    void loadContent() override;

    std::list<Point2d> bullets;
    std::list<Point2d> enemies1;
    std::list<Point2d> enemies2;
    std::list<Point2d> enemies3;
    std::list<Point2d> explosions;
    std::list<Point2d> bangs;
    std::list<Point2d> particles;
    std::vector<Entity> entities;
    
    Entity* player;
    Systems* systems;
    SpriteRenderer* Renderer;
};


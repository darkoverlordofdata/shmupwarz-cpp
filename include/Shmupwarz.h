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
#include "GameSystems.h"
#include "xna/Content/ResourceManager.h"
#include "xna/Graphics/Texture2D.h"
#include "xna/Graphics/Shader.h"
#include "xna/Graphics/SpriteRenderer.h"
#include "xna/Game.h"

enum {
    DISPLAY_WIDTH  = 480,
    DISPLAY_HEIGHT = 320,
    UPDATE_INTERVAL = 1000/60,
    HERO_SPEED = 2
};

class GameSystems;
    
class Shmupwarz : public xna::Game {
friend class GameSystems;
public:
    Shmupwarz(std::string title, int width, int height, SDL_Window* window);
    ~Shmupwarz();
    void Draw() override;
    void Update() override;
    void Initialize() override;
    void LoadContent() override;

    std::list<Point2d> Bullets;
    std::list<Point2d> Enemies1;
    std::list<Point2d> Enemies2;
    std::list<Point2d> Enemies3;
    std::list<Point2d> Explosions;
    std::list<Point2d> Bangs;
    std::list<Point2d> Particles;
    std::vector<Entity> Entities;
    
    Entity* Player;
    GameSystems* Systems;
    xna::graphics::SpriteRenderer* Renderer;
};


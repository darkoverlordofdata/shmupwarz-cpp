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
#include "Components.hpp"
#include "Entities.hpp"
#include "IGameSystems.hpp"
#include "xna/xna.hpp"
#include "xna/SDL/SDLFactory.hpp"
#include "artemis/artemis.hpp"
#include <typeinfo>

using namespace std::chrono;


enum {
    DISPLAY_WIDTH  = 480,
    DISPLAY_HEIGHT = 320,
    UPDATE_INTERVAL = 1000/60,
    HERO_SPEED = 2
};

class IGameSystems;
    
class Shmupwarz : public xna::Game {
friend class IGameSystems;
public:

    std::list<Point2D> Bullets;
    std::list<Point2D> Enemies1;
    std::list<Point2D> Enemies2;
    std::list<Point2D> Enemies3;
    std::list<Point2D> Explosions;
    std::list<Point2D> Bangs;
    std::list<Point2D> Particles;
    std::vector<Entity> Entities;
    
    Entity* Player;
    IGameSystems* Systems;
    xna::graphics::SpriteRenderer* Renderer;

    Shmupwarz(std::string t, int width, int height)
        : Game(new xna::SDLFactory(), t, width, height) {
        std::srand(std::time(0));    

    }

    ~Shmupwarz() {
        Game::Stop();
    }

    /**
     * Initialize the game
     */
    void SetSystem(IGameSystems* systems) {

        Systems = systems;
    }


    /**
     * Draw the frame
     */
    void Draw() {
        // Render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (int i=0; i<Entities.size(); i++) 
            Systems->DrawSystem(Renderer, &Entities[i]);
        // fpsChanged(fps);
        SDL_GL_SwapWindow(Window());
    }

    /**
     * Update game logic
     */
    void Update() 
    {
        Systems->SpawnSystem(Player);
        for (int i=0; i<Entities.size(); i++) Systems->CollisionSystem(&Entities[i]);
        for (int i=0; i<Entities.size(); i++) Systems->EntitySystem(&Entities[i]);
        Systems->InputSystem(Player);
        for (int i=0; i<Entities.size(); i++) Systems->PhysicsSystem(&Entities[i]);
        for (int i=0; i<Entities.size(); i++) Systems->ExpireSystem(&Entities[i]);
        for (int i=0; i<Entities.size(); i++) Systems->TweenSystem(&Entities[i]);
        for (int i=0; i<Entities.size(); i++) Systems->RemoveSystem(&Entities[i]);

    }

    /**
     * load game resources
     */
    void LoadContent() {
        // Load shaders
        xna::ResourceManager::LoadShader("assets/shaders/sprite.vs", "assets/shaders/sprite.frag", nullptr, "sprite");
        xna::ResourceManager::LoadShader("assets/shaders/particle.vs", "assets/shaders/particle.frag", nullptr, "particle");

        // Configure shaders
        glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(Width()), static_cast<GLfloat>(Height()), 0.0f, -1.0f, 1.0f);
        xna::ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
        xna::ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
        xna::ResourceManager::GetShader("particle").Use().SetInteger("sprite", 0);
        xna::ResourceManager::GetShader("particle").SetMatrix4("projection", projection);

        // Load textures
        xna::ResourceManager::LoadTexture("assets/images/background.png", GL_TRUE, "background");
        xna::ResourceManager::LoadTexture("assets/images/bang.png", GL_TRUE, "bang");
        xna::ResourceManager::LoadTexture("assets/images/bullet.png", GL_TRUE, "bullet");
        xna::ResourceManager::LoadTexture("assets/images/enemy1.png", GL_TRUE, "enemy1");
        xna::ResourceManager::LoadTexture("assets/images/enemy2.png", GL_TRUE, "enemy2");
        xna::ResourceManager::LoadTexture("assets/images/enemy3.png", GL_TRUE, "enemy3");
        xna::ResourceManager::LoadTexture("assets/images/explosion.png", GL_TRUE, "explosion");
        xna::ResourceManager::LoadTexture("assets/images/particle.png", GL_TRUE, "particle");
        xna::ResourceManager::LoadTexture("assets/images/spaceshipspr.png", GL_TRUE, "spaceshipspr");
        xna::ResourceManager::LoadTexture("assets/images/star.png", GL_TRUE, "star");

        Entities.reserve(141);
        CreateBackground(&Entities);
        for (int i=0; i<12; i++)    CreateBullet(&Entities);
        for (int i=0; i<15; i++)    CreateEnemy1(&Entities);
        for (int i=0; i<5; i++)     CreateEnemy2(&Entities);
        for (int i=0; i<4; i++)     CreateEnemy3(&Entities);
        for (int i=0; i<10; i++)    CreateExplosion(&Entities);
        for (int i=0; i<12; i++)    CreateBang(&Entities);
        for (int i=0; i<100; i++)   CreateParticle(&Entities);
        Player = CreatePlayer(&Entities);

        // Set render-specific controls
        Renderer = new xna::SpriteRenderer(xna::ResourceManager::GetShader("sprite"));

    }
};


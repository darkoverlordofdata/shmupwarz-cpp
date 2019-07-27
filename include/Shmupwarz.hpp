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

    std::list<Point2d> Bullets;
    std::list<Point2d> Enemies1;
    std::list<Point2d> Enemies2;
    std::list<Point2d> Enemies3;
    std::list<Point2d> Explosions;
    std::list<Point2d> Bangs;
    std::list<Point2d> Particles;
    std::vector<Entity> Entities;
    
    Entity* Player;
    IGameSystems* Systems;
    xna::graphics::SpriteRenderer* Renderer;
    xna::SDLFactory platform;

    Shmupwarz(std::string t, int width, int height, SDL_Window* w)
        : Game(&platform, t, width, height, w) {
        // Systems = new Systems(this);
    }

    ~Shmupwarz() {
        // Systems->dispose();
        Game::Stop();
    }

    /**
     * Initialize the game
     */
    void SetSystem(IGameSystems* systems) {
        Systems = systems;
        
        delete artemis::ComponentFactory::New("A::DerivedA");
        delete artemis::ComponentFactory::New("B::DerivedB");
        delete artemis::ComponentFactory::New("C::DerivedC");
        delete artemis::ComponentFactory::New("D::DerivedD");
        // const std::type_info& ti1 = typeid(this);
        // const std::type_info& ti2 = typeid(Systems);

        // printf("TYPE = %s\n", ti1.name());
        // printf("TYPE = %s\n", ti2.name());

        // auto test = new artemis::Aspect();

        // printf("1>\n");
        // auto bb = new artemis::BlackBoard();
        // printf("2>\n");
        // bb->SetEntry("number", 1);
        // printf("3\n");
        // bb->SetEntry("frodo", test);
        // printf("4>\n");

        // auto n = bb->GetEntry<int>("number");
        // printf("Number = %d\n", n);
        // auto tst1 = bb->GetEntry<artemis::Aspect*>("frodo");
        // printf("String = %s\n", tst1->GetTest().c_str());
    }


    /**
     * Draw the frame
     */
    void Draw() {
        // Render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (int i=0; i<Entities.size(); i++) {
            if (!Entities[i].Active) continue;

            glm::vec3 color(1, 1, 1);

            auto texture = Entities[i].Sprite.Texture;
            if (Entities[i].Tint) {
                color[0] = (float)Entities[i].Tint.value()->R/255.0;
                color[1] = (float)Entities[i].Tint.value()->G/255.0;
                color[2] = (float)Entities[i].Tint.value()->B/255.0;
            }

            Renderer->DrawSprite(texture, 
                {   Entities[i].Bounds.x, 
                    Entities[i].Bounds.y },
                {   Entities[i].Bounds.w, 
                    Entities[i].Bounds.h }, 
                0.0f, color);

        }
        // fpsChanged(fps);
        SDL_GL_SwapWindow(Window());
    }

    /**
     * Update game logic
     */
    void Update() {

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


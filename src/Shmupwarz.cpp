#include "Shmupwarz.h"

using namespace std::chrono;

Shmupwarz::Shmupwarz(std::string t, int width, int height, SDL_Window* w)
    : GameBase(t, width, height, w) {
    // Systems = new Systems(this);
}

Shmupwarz::~Shmupwarz() {
    // Systems->dispose();
    GameBase::Stop();
}

/**
 * Draw the frame
 */
void Shmupwarz::Draw() {
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
    SDL_GL_SwapWindow(Window);
}

/**
 * Update game logic
 */
void Shmupwarz::Update() {

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
 * Initialize the game
 */
void Shmupwarz::Init() {
    Systems = new GameSystems(this);
}

/**
 * load game resources
 */
void Shmupwarz::LoadContent() {
    // Load shaders
    xna::ResourceManager::LoadShader("assets/shaders/sprite.vs", "assets/shaders/sprite.frag", nullptr, "sprite");
    xna::ResourceManager::LoadShader("assets/shaders/particle.vs", "assets/shaders/particle.frag", nullptr, "particle");

    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
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


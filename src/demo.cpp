#include "demo.h"
#include "resource_manager.h"
#include "sprite_renderer.h"

SpriteRenderer    *SpriteBatch;

Demo::Demo(std::string t, int width, int height, SDL_Window* w)
    : title(t), width(width), height(height), window(w), frameSkip(0), running(0) {}

Demo::~Demo() {
    stop();
}

int Demo::getKey(int key) {
    if (key > 255) return 0;
    return keys[key];
}
int Demo::isRunning() {
    return running;
}

void Demo::start() {
    init();
    systems = new Systems(this);
    running = 1;
}


void Demo::draw(int fps, SDL_Rect *clip) {
    if (this->fps != fps) fpsChanged(fps);
    // Render
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i=0; i<entities.size(); i++) {
        if (!entities[i].active) continue;

        glm::vec3 color(1, 1, 1);

        auto texture = entities[i].sprite.texture;
        if (entities[i].tint) {
            color[0] = (float)entities[i].tint.value()->r/255.0;
            color[1] = (float)entities[i].tint.value()->g/255.0;
            color[2] = (float)entities[i].tint.value()->b/255.0;
        }

        SpriteBatch->DrawSprite(texture, 
            {   entities[i].bounds.x, 
                entities[i].bounds.y },
            {   entities[i].bounds.w, 
                entities[i].bounds.h }, 
            0.0f, color);

    }
    SDL_GL_SwapWindow(window);
}

void Demo::stop() {
}

void Demo::fpsChanged(int fps) {
    char szFps[ 128 ];
    sprintf(szFps, "%s: %d", title.c_str(), fps);
    SDL_SetWindowTitle(window, szFps);
    this->fps = fps;
}

void Demo::quit() {
    running = 0;
}

void Demo::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
            case SDL_QUIT:    
                quit();            
                break;
            case SDL_KEYDOWN: 
                keys[event.key.keysym.sym] = 1;
                break;
            case SDL_KEYUP:   
                keys[ event.key.keysym.sym ] = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouseDown = 1;
                break;
            case SDL_MOUSEBUTTONUP:
                mouseDown = 0;
                break;
            case SDL_MOUSEMOTION:
                mouseX = event.motion.x;
                mouseY = event.motion.y;
                break;
        }
    }    
}

void Demo::update(double delta) {

    this->delta = delta;

    systems->spawnSystem(player);
    for (int i=0; i<entities.size(); i++) systems->collisionSystem(&entities[i]);
    for (int i=0; i<entities.size(); i++) systems->entitySystem(&entities[i]);
    systems->inputSystem(player);
    for (int i=0; i<entities.size(); i++) systems->physicsSystem(&entities[i]);
    for (int i=0; i<entities.size(); i++) systems->expireSystem(&entities[i]);
    for (int i=0; i<entities.size(); i++) systems->tweenSystem(&entities[i]);
    for (int i=0; i<entities.size(); i++) systems->removeSystem(&entities[i]);

}

void Demo::init() {

    // Load shaders
    ResourceManager::LoadShader("assets/shaders/sprite.vs", "assets/shaders/sprite.frag", nullptr, "sprite");
    ResourceManager::LoadShader("assets/shaders/particle.vs", "assets/shaders/particle.frag", nullptr, "particle");

    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    ResourceManager::GetShader("particle").Use().SetInteger("sprite", 0);
    ResourceManager::GetShader("particle").SetMatrix4("projection", projection);

    // Load textures
    ResourceManager::LoadTexture("assets/images/background.png", GL_TRUE, "background");
    ResourceManager::LoadTexture("assets/images/bang.png", GL_TRUE, "bang");
    ResourceManager::LoadTexture("assets/images/bullet.png", GL_TRUE, "bullet");
    ResourceManager::LoadTexture("assets/images/enemy1.png", GL_TRUE, "enemy1");
    ResourceManager::LoadTexture("assets/images/enemy2.png", GL_TRUE, "enemy2");
    ResourceManager::LoadTexture("assets/images/enemy3.png", GL_TRUE, "enemy3");
    ResourceManager::LoadTexture("assets/images/explosion.png", GL_TRUE, "explosion");
    ResourceManager::LoadTexture("assets/images/particle.png", GL_TRUE, "particle");
    ResourceManager::LoadTexture("assets/images/spaceshipspr.png", GL_TRUE, "spaceshipspr");
    ResourceManager::LoadTexture("assets/images/star.png", GL_TRUE, "star");

    entities.reserve(141);
    createBackground(&entities);
    for (int i=0; i<12; i++)    createBullet(&entities);
    for (int i=0; i<15; i++)    createEnemy1(&entities);
    for (int i=0; i<5; i++)     createEnemy2(&entities);
    for (int i=0; i<4; i++)     createEnemy3(&entities);
    for (int i=0; i<10; i++)    createExplosion(&entities);
    for (int i=0; i<12; i++)    createBang(&entities);
    for (int i=0; i<100; i++)   createParticle(&entities);
    player = createPlayer(&entities);

    // Set render-specific controls
    SpriteBatch = new SpriteRenderer(ResourceManager::GetShader("sprite"));

}


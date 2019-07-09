#include "Shmupwarz.h"

using namespace std::chrono;

Shmupwarz::Shmupwarz(std::string t, int width, int height, SDL_Window* w)
    : Game(t, width, height, w) {}
    // : title(t), width(width), height(height), window(w), frameSkip(0), running(0) {}

Shmupwarz::~Shmupwarz() {
    stop();
}

// int Shmupwarz::getKey(int key) {
//     if (key > 255) return 0;
//     return keys[key];
// }
// int Shmupwarz::isRunning() {
//     return running;
// }

// void Shmupwarz::start() {
//     init();
//     systems = new Systems(this);
//     running = 1;
//     auto num = high_resolution_clock::period::num;
//     auto den = high_resolution_clock::period::den;
//     factor = (double)num/(double)den;
//     mark1 = high_resolution_clock::now();

// }


void Shmupwarz::draw() {
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

        Renderer->DrawSprite(texture, 
            {   entities[i].bounds.x, 
                entities[i].bounds.y },
            {   entities[i].bounds.w, 
                entities[i].bounds.h }, 
            0.0f, color);

    }
    // fpsChanged(fps);
    SDL_GL_SwapWindow(window);
}

// void Shmupwarz::stop() {
// }

// void Shmupwarz::fpsChanged(int fps) {
//     char szFps[ 128 ];
//     sprintf(szFps, "%s: %d", title.c_str(), fps);
//     SDL_SetWindowTitle(window, szFps);
//     this->fps = fps;
// }

// void Shmupwarz::quit() {
//     running = 0;
// }

// void Shmupwarz::runLoop() {
//     handleEvents();
//     tick();
// }
// void Shmupwarz::handleEvents() {
//     SDL_Event event;
//     while (SDL_PollEvent(&event) != 0) {
//         switch (event.type) {
//             case SDL_QUIT:    
//                 quit();       
//                 return;     
//                 break;
//             case SDL_KEYDOWN: 
//                 keys[event.key.keysym.sym] = 1;
//                 if (event.key.keysym.sym == SDLK_ESCAPE) {
//                     quit();       
//                     return;     
//                 }
//                 break;
//             case SDL_KEYUP:   
//                 keys[ event.key.keysym.sym ] = 0;
//                 break;
//             case SDL_MOUSEBUTTONDOWN:
//                 mouseDown = 1;
//                 break;
//             case SDL_MOUSEBUTTONUP:
//                 mouseDown = 0;
//                 break;
//             case SDL_MOUSEMOTION:
//                 mouseX = event.motion.x;
//                 mouseY = event.motion.y;
//                 break;
//         }
//     }
// }

// void Shmupwarz::tick() {
//     mark2 = high_resolution_clock::now();
//     delta += ((double) duration_cast<nanoseconds>(mark2 - mark1).count()) * factor;
//     ticks += 1;
//     mark1 = mark2;
//     if (delta >= 0.01667) {
//         update();
//         draw();
//         printf("%f -- %d\n", delta, ticks);
//         delta = 0.0;
//         ticks = 0;
//     }

// }

void Shmupwarz::update() {

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

void Shmupwarz::init() {

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
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

}


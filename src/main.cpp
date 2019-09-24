#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <chrono>
#include <iostream>
#ifdef __EMSCRIPTEN__
#include <functional>
#include <emscripten.h>
std::function<void()> loop;
void main_loop() { loop(); }
#else
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#include "IGameSystems.hpp"
#include "Shmupwarz.hpp"
#include "GameSystems.hpp"

using namespace std::chrono;

namespace A {
    class DerivedA : public artemis::Component { 
      public:
        DerivedA() {
            std::cout << "A::DerivedA constructor\n"; 
        } 
    }; 
}
RegisterType(A::DerivedA);

namespace B { class DerivedB : public artemis::Component { public: DerivedB() { std::cout << "B::DerivedB constructor\n"; } }; }
RegisterType(B::DerivedB);

namespace C { class DerivedC : public artemis::Component { public: DerivedC() { std::cout << "C::DerivedC constructor\n"; } }; }
RegisterType(C::DerivedC);

namespace D { class DerivedD : public artemis::Component { public: DerivedD() { std::cout << "D::DerivedD constructor\n"; } }; }
RegisterType(D::DerivedD);

int main(int argc, char** argv){

    Shmupwarz game("Shmupwarz", 900, 600);
    game.SetSystem(new GameSystems(&game));
    game.Run();

    printf("That's all folks!\n");
    return 0;
}


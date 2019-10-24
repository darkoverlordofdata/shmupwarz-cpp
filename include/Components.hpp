#pragma once
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <cstdio>
#include <map>
#include <string>
#include <iostream>
#include <ctime>
#include <chrono>
#include <vector>
#include <random>

#include <experimental/optional>

#include "artemis/artemis.hpp"
#include "xna/Graphics/Texture2D.hpp"

using namespace std; //::experimental;

#define RegisterComponent(T) template<> artemis::Component::Creator_t* artemis::Component::Register<T>::Creator = artemis::Component::Register<T>::Init_creator(#T)


enum class TypeOf {
    NONE,
    BACKGROUND,
    TEXT,
    LIVES,
    ENEMY1,
    ENEMY2,
    ENEMY3,
    PLAYER,
    BULLET,
    EXPLOSION,
    BANG,
    PARTICLE,
    HUD
};
enum class CategoryOf {
    NONE,
    BACKGROUND,
    BULLET,
    ENEMY,
    EXPLOSION,
    PARTICLE,
    PLAYER
};

class Sound : public artemis::Component {
public:
    Sound(){}
    Sound(char* path) : Chunk(Mix_LoadWAV(path)) {}
    Mix_Chunk* Chunk;
};
RegisterComponent(Sound);

class Point2D : public artemis::Component {
public:
    Point2D(): X(0), Y(0) {}
    Point2D(double x, double y): X(x), Y(y) {}
    double X;
    double Y;
};
RegisterComponent(Point2D);

class Vector2D : public artemis::Component {
public:
    Vector2D(): X(0), Y(0) {}
    Vector2D(double x, double y): X(x), Y(y) {}
    double X;
    double Y;
};
RegisterComponent(Vector2D);

class Timer : public artemis::Component {
public:
    Timer(): Milli(0) {}
    Timer(double ms): Milli(ms) {}
    double Milli;
};
RegisterComponent(Timer);

class Scale : public artemis::Component {
public:
    Scale(): X(0), Y(0) {}
    Scale(double x, double y): X(x), Y(y) {}
    double X;
    double Y;
};
RegisterComponent(Scale);

class Color : public artemis::Component {
public:
    Color(): R(0), G(0), B(0), A(0) {}
    Color(int r, int g, int b, int a): R(r), G(g), B(b), A(a) {}
    int R;
    int G;
    int B;
    int A;
};
RegisterComponent(Color);

class Health : public artemis::Component {
public:
    Health(): Current(0), Maximum(0) {}
    Health(int c, int m): Current(c), Maximum(m) {}
    int Current;
    int Maximum;
};
RegisterComponent(Health);

class Tween : public artemis::Component {
public:
    Tween(): Min(0), Max(0), Speed(0), Repeat(false), Active(false) {}
    Tween(double m, double x, double s, bool r, bool a): Min(m), Max(x), Speed(s), Repeat(r), Active(a) {}
    double Min;
    double Max;
    double Speed;
    bool Repeat;
    bool Active;
};
RegisterComponent(Tween);

class Transform : public artemis::Component {
public:
    Transform(): Texture(nullptr), Bounds({0, 0, 0, 0}), Pos {0, 0}, Scale({0, 0}) {}
    Transform(xna::graphics::Texture2D* texture): 
        Texture (texture), 
        Bounds ({0, 0, (int)texture->Width, (int)texture->Height}), 
        Pos ({0, 0}), 
        Scale ({1, 1}) {}
    Transform(xna::graphics::Texture2D* texture, double scale): 
        Texture (texture), 
        Bounds ({0, 0, (int)(texture->Width*scale), (int)(texture->Height*scale) }), 
        Pos ({0, 0}), 
        Scale ({scale, scale}) {}

    xna::graphics::Texture2D* Texture;
    SDL_Rect Bounds;
    Vector2D Pos;
    Vector2D Scale;
};
RegisterComponent(Transform);

class Identity : public artemis::Component {
public:
    Identity(): Type(TypeOf::NONE), Category(CategoryOf::NONE) {}
    Identity(TypeOf type, CategoryOf category):Type(type), Category(category) {}

    TypeOf Type;
    CategoryOf Category;
};
RegisterComponent(Identity);


class Entity {
public:
    Entity(int id, std::string name, bool active): Id(id), Name(name), Active(active) {}
    
    int Id;
    std::string Name;
    bool Active;

    optional<Transform*> Transform;
    optional<Identity*> Identity;
    optional<Sound*> Sound;
    optional<Color*> Tint;
    optional<Timer*> Expires;
    optional<Health*> Health;
    optional<Tween*> Tween;
    optional<Vector2D*> Velocity;

};



// #endif
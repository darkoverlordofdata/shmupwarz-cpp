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

#include "xna/Graphics/Texture2D.hpp"

using namespace std::experimental;


enum class TypeOf {
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
    BACKGROUND,
    BULLET,
    ENEMY,
    EXPLOSION,
    PARTICLE,
    PLAYER
};

enum class Effect {
    PEW,
    SMALLASPLODE,
    ASPLODE
};

class Point2d {
public:
    Point2d(): X(0), Y(0) {}
    Point2d(double x, double y): X(x), Y(y) {}
    double X;
    double Y;
};

class Vector2d {
public:
    Vector2d(): X(0), Y(0) {}
    Vector2d(double x, double y): X(x), Y(y) {}
    double X;
    double Y;
};

class Scale {
public:
    Scale(): X(0), Y(0) {}
    Scale(double x, double y): X(x), Y(y) {}
    double X;
    double Y;
};

class Color {
public:
    Color(): R(0), G(0), B(0), A(0) {}
    Color(int r, int g, int b, int a): R(r), G(g), B(b), A(a) {}
    int R;
    int G;
    int B;
    int A;
};

class Health {
public:
    Health(): Current(0), Maximum(0) {}
    Health(int c, int m): Current(c), Maximum(m) {}
    int Current;
    int Maximum;
};

class Tween {
public:
    Tween(): Min(0), Max(0), Speed(0), Repeat(false), Active(false) {}
    Tween(double m, double x, double s, bool r, bool a): Min(m), Max(x), Speed(s), Repeat(r), Active(a) {}
    double Min;
    double Max;
    double Speed;
    bool Repeat;
    bool Active;
};

class Sprite {
public:
    xna::graphics::Texture2D Texture;
    int Width;
    int Height;
};


class Entity {
public:
    Entity(int id, std::string name, bool active): Id(id), Name(name), Active(active) {}
    
    int Id;
    std::string Name;
    bool Active;
    TypeOf Type;
    CategoryOf Category;
    Point2d Position;
    SDL_Rect Bounds;
    Vector2d Scale;
    Sprite Sprite;

    optional<Effect> Sound;
    optional<Color*> Tint;
    optional<double> Expires;
    optional<Health*> Health;
    optional<Tween*> Tween;
    optional<Vector2d*> Velocity;


};



// #endif
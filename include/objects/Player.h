#pragma once

extern "C"
{
#include "raylib.h"
}
#include <string>
#include "tiled/TiledMap.h"

struct Animation
{
    int frame = 0;
    int frameCount = 4;
    int frameWidth = 32;
    int frameHeight = 32;
    float frameTime = 0.1f;
    float timer = 0.0f;
};

class Player
{
public:
    void Init(Vector2 spawnPosition);
    void Update(const TiledMap *map);
    void Draw() const;
    const Vector2 &GetPosition() const;

private:
    Vector2 position;
    Texture2D texture;
    Vector2 size = {32, 32};
    Vector2 velocity = {0, 0};
    float gravity = 500.0f;
    float moveSpeed = 100.0f;
    float jumpVelocity = -200.0f;
    bool onGround = false;
};
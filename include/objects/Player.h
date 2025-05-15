#pragma once

extern "C"
{
#include "raylib.h"
}
#include <string>
#include "tiled/TiledMap.h"

enum class PlayerState
{
    IDLE,
    RUNNING,
    ROLLING,
    JUMPING,
    HIT,
    DEATH
};

enum class PlayerDirection
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Player
{
public:
    void Init(Vector2 spawnPosition);
    void Update(const TiledMap *map);
    void Draw() const;
    const Vector2 &GetPosition() const;

private:
    void HandleInput();
    void GroundCheck(const TiledMap *map);
    Vector2 position;
    Texture2D texture;
    Vector2 size = {32, 32};
    Vector2 velocity = {0, 0};
    float gravity = 500.0f;
    float moveSpeed = 100.0f;
    float jumpVelocity = -200.0f;
    bool onGround = true;
    PlayerDirection direction = PlayerDirection::RIGHT;
    PlayerState state = PlayerState::IDLE;
};
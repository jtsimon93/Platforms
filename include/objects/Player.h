#pragma once

extern "C"
{
#include "raylib.h"
}

#include <string>
#include "tiled/TiledMap.h"
#include "objects/Sprite.h"

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
    ~Player() = default;

    void Init(Vector2 spawnPosition);

    void Update(const TiledMap *map, float deltaTime);

    void Draw() const;

    const Vector2 &GetPosition() const;

    const Rectangle GetCollisionRect() const;

private:
    void HandleInput();

    void GroundCheck(const TiledMap *map);

    void CollisionCheck(const TiledMap *map);

    void UpdateAnimation();

    Vector2 position = {0, 0};
    Vector2 hitboxSize = {24, 28};
    Vector2 velocity = {0, 0};
    float gravity = 500.0f;
    float moveSpeed = 100.0f;
    float jumpVelocity = -200.0f;
    bool onGround = true;
    PlayerDirection direction = PlayerDirection::RIGHT;
    PlayerState state = PlayerState::IDLE;
    PlayerState previousState = PlayerState::IDLE;

    Sprite sprite;
};

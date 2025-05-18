#pragma once

extern "C"
{
#include "raylib.h"
}

#include "objects/Sprite.h"

enum class CoinState
{
    IDLE,
    COLLECTED
};

class Coin
{
public:
    ~Coin() = default;

    void Init(Vector2 spawnPosition);
    void Update(float deltaTime);
    void Draw() const;
    const Vector2 &GetPosition() const;
    const int GetValue() const;
    const Rectangle GetCollisionRect() const;

private:
    Vector2 position = {0, 0};
    Sprite sprite;
    const int value = 1;
    const Vector2 size = {16, 16};
};
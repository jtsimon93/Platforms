#pragma once

extern "C"
{
#include "raylib.h"
}
#include <string>

class Player
{
public:
    void Init(Vector2 spawnPosition, const std::string &spritePath);
    void Update();
    void Draw() const;

private:
    Vector2 position;
    Texture2D texture;
    Vector2 size = {32, 32};
};
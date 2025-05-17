#include "objects/Coin.h"

void Coin::Init(Vector2 spawnPosition)
{
    position = spawnPosition;
    const std::string spritePath = "assets/brackeys_platformer_assets/sprites/coin.png";
    sprite.LoadSpriteTexture(spritePath);
    sprite.SetOffset({0.0f, 0.0f});

    const std::vector<AnimationFrame> defaultFrames = {
        {Rectangle{0, 0, 16, 16}, 0.0833f},   // Frame 1
        {Rectangle{16, 0, 16, 16}, 0.0833f},  // Frame 2
        {Rectangle{32, 0, 16, 16}, 0.0833f},  // Frame 3
        {Rectangle{48, 0, 16, 16}, 0.0833f},  // Frame 4
        {Rectangle{64, 0, 16, 16}, 0.0833f},  // Frame 5
        {Rectangle{80, 0, 16, 16}, 0.0833f},  // Frame 6
        {Rectangle{96, 0, 16, 16}, 0.0833f},  // Frame 7
        {Rectangle{112, 0, 16, 16}, 0.0833f}, // Frame 8
        {Rectangle{128, 0, 16, 16}, 0.0833f}, // Frame 9
        {Rectangle{144, 0, 16, 16}, 0.0833f}, // Frame 10
        {Rectangle{160, 0, 16, 16}, 0.0833f}, // Frame 11
        {Rectangle{176, 0, 16, 16}, 0.0833f}  // Frame 12
    };

    sprite.AddAnimation("default", defaultFrames);

    sprite.SetAnimation("default");
}

void Coin::Update(float deltaTime)
{
    sprite.Update(deltaTime);
}

void Coin::Draw() const
{
    sprite.Draw(position);
}

const Vector2 &Coin::GetPosition() const
{
    return position;
}

const int Coin::GetValue() const
{
    return value;
}

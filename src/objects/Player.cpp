#include "objects/Player.h"

void Player::Init(Vector2 spawnPosition, const std::string &spritePath)
{
    position = spawnPosition;
    texture = LoadTexture(spritePath.c_str());
}

void Player::Update()
{
    // Not implemented yet
}

void Player::Draw() const
{
    Vector2 drawPosition = position;
    drawPosition.y -= (size.y);

    DrawTextureRec(texture, {0, 0, size.x, size.y}, drawPosition, WHITE);
}
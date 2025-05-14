#include "objects/Player.h"

void Player::Init(Vector2 spawnPosition)
{
    position = spawnPosition;
    const std::string spritePath = "assets/brackeys_platformer_assets/sprites/knight.png";
    texture = LoadTexture(spritePath.c_str());
}

void Player::Update(const TiledMap *map)
{
    float dt = GetFrameTime();

    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    {
        velocity.x = -moveSpeed;
    }
    else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    {
        velocity.x = moveSpeed;
    }
    else
    {
        velocity.x = 0;
    }

    if (onGround && (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)))
    {
        velocity.y = jumpVelocity;
        onGround = false;
    }

    velocity.y += gravity * dt;

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    // Ground check
    onGround = false;
    Vector2 probe = {position.x + size.x / 2, position.y + 1};

    if (map->IsTileSolid(probe))
    {
        onGround = true;
        velocity.y = 0;

        // snap to ground
        position.y = ((int)(position.y / 16)) * 16;
    }
}

void Player::Draw() const
{
    Vector2 drawPosition = position;
    drawPosition.y -= (size.y);

    DrawTextureRec(texture, {0, 0, size.x, size.y}, drawPosition, WHITE);
}
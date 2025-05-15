#include "objects/Player.h"
#include <cmath>

void Player::Init(const Vector2 spawnPosition)
{
    position = spawnPosition;
    const std::string spritePath = "assets/brackeys_platformer_assets/sprites/knight.png";
    texture = LoadTexture(spritePath.c_str());
}

void Player::HandleInput()
{
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    {
        velocity.x = -moveSpeed;
        direction = PlayerDirection::LEFT;
        state = PlayerState::RUNNING;
    }
    else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    {
        velocity.x = moveSpeed;
        direction = PlayerDirection::RIGHT;
        state = PlayerState::RUNNING;
    }
    else
    {
        velocity.x = 0;
        state = PlayerState::IDLE;
    }

    if (onGround && (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)))
    {
        velocity.y = jumpVelocity;
        state = PlayerState::JUMPING;
    }
}

void Player::GroundCheck(const TiledMap *map) {
    const Vector2 probe = {
        position.x + size.x / 2.0f,
        position.y + 1.0f
    };

    // Use below to debug ground check
    //DrawCircle(static_cast<int>(probe.x), static_cast<int>(probe.y), 2.0f, RED);

    if (map->IsTileSolid(probe))
    {
        onGround = true;
        velocity.y = 0;

        // snap to ground
        position.y = std::floor((position.y + size.y) / 16.0f) * 16.0f - size.y;
    }
    else {
        onGround = false;
    }
}

void Player::Update(const TiledMap *map)
{
    GroundCheck(map);
    HandleInput();

    const float dt = GetFrameTime();
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
    velocity.y += gravity * dt;
}

void Player::Draw() const
{
    Vector2 drawPosition = position;
    drawPosition.y -= (size.y) - 5; // Adjust for sprite height
    DrawTextureRec(texture, {0, 0, size.x, size.y}, drawPosition, WHITE);
}

const Vector2 &Player::GetPosition() const
{
    return position;
}
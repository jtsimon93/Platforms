#include "objects/Player.h"
#include <cmath>
#include <iostream>

void Player::Init(const Vector2 spawnPosition) {
    position = spawnPosition;
    const std::string spritePath = "assets/brackeys_platformer_assets/sprites/knight.png";
    sprite.LoadSpriteTexture(spritePath);
    sprite.SetOffset({0, -(sprite.GetSize().y / 2) - 32 + 5}); // Adjust for sprite height

    sprite.SetScale(1.0f);

    // Idle animation
    const std::vector<AnimationFrame> idleFrames = {
        {Rectangle{0, 0, 32, 32}, 0.2f},
        {Rectangle{32, 0, 32, 32}, 0.2f},
        {Rectangle{64, 0, 32, 32}, 0.2f},
        {Rectangle{96, 0, 32, 32}, 0.2f}
    };
    sprite.AddAnimation("idle", idleFrames);

    // Running animation - 16 frames (8 on each of 2 rows)
    const std::vector<AnimationFrame> runningFrames = {
        // First row of running frames
        {Rectangle{0, 64, 32, 32}, 0.1f}, // Frame 1
        {Rectangle{32, 64, 32, 32}, 0.1f}, // Frame 2
        {Rectangle{64, 64, 32, 32}, 0.1f}, // Frame 3
        {Rectangle{96, 64, 32, 32}, 0.1f}, // Frame 4
        {Rectangle{128, 64, 32, 32}, 0.1f}, // Frame 5
        {Rectangle{160, 64, 32, 32}, 0.1f}, // Frame 6
        {Rectangle{192, 64, 32, 32}, 0.1f}, // Frame 7
        {Rectangle{224, 64, 32, 32}, 0.1f}, // Frame 8

        // Second row of running frames
        {Rectangle{0, 96, 32, 32}, 0.1f}, // Frame 9
        {Rectangle{32, 96, 32, 32}, 0.1f}, // Frame 10
        {Rectangle{64, 96, 32, 32}, 0.1f}, // Frame 11
        {Rectangle{96, 96, 32, 32}, 0.1f}, // Frame 12
        {Rectangle{128, 96, 32, 32}, 0.1f}, // Frame 13
        {Rectangle{160, 96, 32, 32}, 0.1f}, // Frame 14
        {Rectangle{192, 96, 32, 32}, 0.1f}, // Frame 15
        {Rectangle{224, 96, 32, 32}, 0.1f}, // Frame 16
    };
    sprite.AddAnimation("running", runningFrames);

    // Jumping animation
    const std::vector<AnimationFrame> jumpingFrames = {
        {Rectangle{0, 64, 32, 32}, 0.1f},
    };
    sprite.AddAnimation("jumping", jumpingFrames);

    // Set initial animation
    sprite.SetAnimation("idle");
}

void Player::UpdateAnimation() {
    if (state != previousState) {
        switch (state) {
            case PlayerState::IDLE:
                sprite.SetAnimation("idle");
                break;
            case PlayerState::RUNNING:
                sprite.SetAnimation("running");
                break;
            case PlayerState::JUMPING:
                sprite.SetAnimation("jumping");
                break;
            default:
                sprite.SetAnimation("idle");
                break;
        }
    }
    previousState = state;
}

void Player::HandleInput() {
    if (onGround && (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))) {
        onGround = false;
        velocity.y = jumpVelocity;
        state = PlayerState::JUMPING;
    }

    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        velocity.x = -moveSpeed;
        direction = PlayerDirection::LEFT;
        state = PlayerState::RUNNING;
    } else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        velocity.x = moveSpeed;
        direction = PlayerDirection::RIGHT;
        state = PlayerState::RUNNING;
    } else {
        velocity.x = 0;
        state = PlayerState::IDLE;
    }
}

void Player::CollisionCheck(const TiledMap *map) {
    GroundCheck(map);
}

void Player::GroundCheck(const TiledMap *map) {
    const Vector2 probe = {
        position.x + sprite.GetSize().x / 2.0f,
        position.y + 1.0f
    };

    // Use below to debug ground check
    // DrawCircle(static_cast<int>(probe.x), static_cast<int>(probe.y), 2.0f, RED);

    if (map->IsTileSolid(probe)) {
        onGround = true;
        velocity.y = 0;

        // snap to ground
        position.y = std::floor((position.y + sprite.GetSize().y) / 16.0f) * 16.0f - sprite.GetSize().y;
    } else {
        onGround = false;
    }
}

void Player::Update(const TiledMap *map, float deltaTime) {
    CollisionCheck(map);
    HandleInput();

    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    velocity.y += gravity * deltaTime;

    if (!onGround) {
        // For now let's use jumping but might need something for falling later
        state = PlayerState::JUMPING;
    }

    UpdateAnimation();
    sprite.Update(deltaTime);
}

void Player::Draw() const {
    sprite.Draw(position, direction == PlayerDirection::LEFT);
}

const Vector2 &Player::GetPosition() const {
    return position;
}

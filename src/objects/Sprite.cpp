#include "objects/Sprite.h"

Sprite::Sprite() : texture({0}), currentFrame(0),
                   frameTimer(0.0f), sourceRect({0}),
                   offset({0.0f, 0.0f}),
                   scale(1.0f) {
}

Sprite::~Sprite() {
    UnloadTexture(texture);
}

void Sprite::LoadSpriteTexture(const std::string &texturePath) {
    texture = LoadTexture(texturePath.c_str());
}

void Sprite::AddAnimation(const std::string &name, const std::vector<AnimationFrame> &frames) {
    animations[name] = frames;

    if (currentAnimation.empty()) {
        SetAnimation(name);
    }
}

void Sprite::SetAnimation(const std::string &name) {
    if (currentAnimation != name && animations.find(name) != animations.end()) {
        currentAnimation = name;
        currentFrame = 0;
        frameTimer = 0.0f;

        sourceRect = animations[name][0].sourceRect;
    }
}

void Sprite::Update(float deltaTime) {
    if (animations.empty() || currentAnimation.empty()) {
        return;
    }

    auto &frames = animations[currentAnimation];

    frameTimer += deltaTime;

    if (frameTimer >= frames[currentFrame].duration) {
        frameTimer = 0.0f;
        currentFrame = (currentFrame + 1) % frames.size();
        sourceRect = frames[currentFrame].sourceRect;
    }
}

void Sprite::Draw(const Vector2 &position, bool flipX) const {
    Vector2 drawPosition = position;
    drawPosition.x += offset.x;
    drawPosition.y += offset.y;

    // Draw the sprite
    if (flipX) {
        // For flipped drawing, we need to adjust the position
        DrawTexturePro(
            texture,
            {sourceRect.x, sourceRect.y, -sourceRect.width, sourceRect.height}, // Negative width flips horizontally
            {drawPosition.x, drawPosition.y, sourceRect.width * scale, sourceRect.height * scale},
            {0, 0},
            0.0f,
            WHITE);
    } else {
        DrawTextureRec(texture, sourceRect, drawPosition, WHITE);
    }
}

void Sprite::SetOffset(const Vector2 &offset) {
    this->offset = offset;
}

void Sprite::SetScale(const float scale) {
    this->scale = scale;
}

Vector2 Sprite::GetSize() const {
    return {sourceRect.width * scale, sourceRect.height * scale};
}

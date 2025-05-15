#pragma once

extern "C" {
#include "raylib.h"
}

#include <string>
#include <map>
#include <vector>

struct AnimationFrame {
    Rectangle sourceRect;
    float duration;
};

class Sprite {
public:
    Sprite();

    ~Sprite();

    void LoadSpriteTexture(const std::string &texturePath);

    void AddAnimation(const std::string &name, const std::vector<AnimationFrame> &frames);

    void SetAnimation(const std::string &name);

    void Update(float deltaTime);

    void Draw(const Vector2 &position, bool flipX = false) const;

    void SetOffset(const Vector2 &offset);

    void SetScale(float scale);

    Vector2 GetSize() const;

private:
    Texture2D texture{};
    std::map<std::string, std::vector<AnimationFrame> > animations;
    std::string currentAnimation;
    int currentFrame;
    float frameTimer;
    Rectangle sourceRect{};
    Vector2 offset;
    float scale;
};

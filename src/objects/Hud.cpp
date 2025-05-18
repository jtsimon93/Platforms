#include "objects/Hud.h"
#include <string>

Hud::Hud() : score(0), lives(0), textColor(RAYWHITE), fontSize(20), padding(10) {}

void Hud::Init(const int score, const int lives) {
    this->score = score;
    this->lives = lives;
    this->textColor = RED;
    this->fontSize = 20;
    this->padding = 10;
}

void Hud::Update(const int score, const int lives)
{
    this->score = score;
    this->lives = lives;
}

void Hud::Draw() const {
    std::string scoreText = "SCORE: " + std::to_string(score);
    DrawText(scoreText.c_str(), padding, padding, fontSize, textColor);

    std::string livesText = "LIVES: " + std::to_string(lives);
    int livesTextWidth = MeasureText(livesText.c_str(), fontSize);
    int screenWidth = GetScreenWidth();
    DrawText(livesText.c_str(), screenWidth - livesTextWidth - padding, padding, fontSize, textColor);
}

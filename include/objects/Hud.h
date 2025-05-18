#pragma once

extern "C" {
    #include "raylib.h"
}

class Hud {
public:
  Hud();
  ~Hud() = default;
  void Init(const int score, const int lives);
  void Update(const int score, const int lives);
  void Draw() const;

private:
  int score;
  int lives;
  Color textColor;
  int fontSize;
  int padding;
};

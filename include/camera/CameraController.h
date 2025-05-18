#pragma once

extern "C" {
#include "raylib.h"
}

class CameraController {
public:
  void Init(float screenWidth, float screenHeight, float zoom = 2.0f);
  void Update(const Vector2 &targetPosition);
  void Begin() const;
  void End() const;
  const Camera2D &GetRaylibCamera() const;

private:
  Camera2D camera;
};
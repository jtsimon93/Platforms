#include "camera/CameraController.h"

void CameraController::Init(float screenWidth, float screenHeight, float zoom)
{
    camera = {0};
    camera.zoom = zoom;
    camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
}

void CameraController::Update(const Vector2 &targetPosition)
{
    camera.target = {targetPosition.x + 16, targetPosition.y + 16};
}

void CameraController::Begin() const
{
    BeginMode2D(camera);
}

void CameraController::End() const
{
    EndMode2D();
}

const Camera2D &CameraController::GetRaylibCamera() const
{
    return camera;
}
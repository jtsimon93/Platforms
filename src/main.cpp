extern "C"
{
#include "raylib.h"
}
#include <string>

int main()
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    const std::string gameTitle = "Platforms";

    InitWindow(screenWidth, screenHeight, gameTitle.c_str());
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Welcome to Platforms!", screenWidth / 2 - MeasureText("Welcome to Platforms!", 20) / 2, screenHeight / 2 - 10, 20, RAYWHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
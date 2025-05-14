extern "C"
{
#include "raylib.h"
}
#include <string>
#include "tiled/TiledMap.h"
#include "objects/Player.h"

int main()
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    const std::string gameTitle = "Platforms";

    InitWindow(screenWidth, screenHeight, gameTitle.c_str());
    SetTargetFPS(60);

    TiledMap map;
    map.Load("assets/tiled/levels/level1.tmx");

    Player player;
    player.Init(map.GetPlayerSpawn());

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        map.Draw();
        player.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
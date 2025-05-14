extern "C"
{
#include "raylib.h"
}
#include <string>
#include "tiled/TiledMap.h"
#include "objects/Player.h"
#include "camera/CameraController.h"

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

    CameraController camera;
    camera.Init(screenWidth, screenHeight);

    while (!WindowShouldClose())
    {
        camera.Update(player.GetPosition());

        BeginDrawing();
        ClearBackground(BLACK);

        camera.Begin();

        map.Draw();
        player.Update(&map);
        player.Draw();

        camera.End();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
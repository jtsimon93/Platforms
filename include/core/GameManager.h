#pragma once

extern "C"
{
#include "raylib.h"
}

#include <string>
#include "tiled/TiledMap.h"
#include "camera/CameraController.h"
#include "objects/Player.h"

enum class GameState
{
    MAIN_MENU,
    PLAYING,
    PAUSED,
    GAME_OVER
};

class GameManager
{
public:
    GameManager();
    ~GameManager();

    void Init(int screenWidth, int screenHeight, const std::string &gameTitle);
    void Run();
    void Shutdown();

private:
    void HandleInput();
    void Update(float deltaTime);
    void Draw();
    void LoadLevel(const std::string &levelPath);

    int screenWidth;
    int screenHeight;
    std::string gameTitle;
    GameState currentState;

    TiledMap *currentMap;
    Player *player;
    CameraController *camera;

    bool isRunning;
};
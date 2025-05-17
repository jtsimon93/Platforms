#include "core/GameManager.h"

GameManager::GameManager() : screenWidth(800),
                             screenHeight(600),
                             gameTitle("Platforms"),
                             currentState(GameState::PLAYING),
                             currentMap(nullptr),
                             player(nullptr),
                             camera(nullptr),
                             isRunning(true)
{
}

GameManager::~GameManager()
{
    Shutdown();
}

void GameManager::Init(int width, int height, const std::string &title)
{
    screenWidth = width;
    screenHeight = height;
    gameTitle = title;

    InitWindow(screenWidth, screenHeight, gameTitle.c_str());
    SetTargetFPS(60);

    currentMap = new TiledMap();
    currentMap->Load("assets/tiled/levels/level1.tmx");

    player = new Player();
    player->Init(currentMap->GetPlayerSpawn());

    camera = new CameraController();
    camera->Init(static_cast<float>(screenWidth), static_cast<float>(screenHeight));

    for (const auto &coinSpawn : currentMap->GetCoinSpawnPoints())
    {
        auto coin = std::make_unique<Coin>();
        coin->Init(coinSpawn);
        coins.push_back(std::move(coin));
    }

    isRunning = true;
};

void GameManager::Run()
{
    while (isRunning && !WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        HandleInput();
        Update(deltaTime);
        Draw();
    }
};

void GameManager::HandleInput()
{
    if (IsKeyPressed(KEY_P))
    {
        if (currentState == GameState::PLAYING)
        {
            currentState = GameState::PAUSED;
        }
        else if (currentState == GameState::PAUSED)
        {
            currentState = GameState::PLAYING;
        }
    }
}

void GameManager::Update(float deltaTime)
{
    if (currentState != GameState::PLAYING)
    {
        return;
    }

    player->Update(currentMap, deltaTime);
    camera->Update(player->GetPosition());

    for (auto &coin : coins)
    {
        coin->Update(deltaTime);
    }
};

void GameManager::Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    if (currentState == GameState::PLAYING || currentState == GameState::PAUSED)
    {
        camera->Begin();
        currentMap->Draw();
        player->Draw();

        for (const auto &coin : coins)
        {
            coin->Draw();
        }

        camera->End();

        if (currentState == GameState::PAUSED)
        {
            DrawRectangle(0, 0, screenWidth, screenHeight, ColorAlpha(BLACK, 0.5f));
            DrawText("PAUSED", screenWidth / 2 - MeasureText("PAUSED", 40) / 2, screenHeight / 2 - 40, 40, RAYWHITE);
        }
    }

    EndDrawing();
}

void GameManager::Shutdown()
{
    if (player)
    {
        delete player;
        player = nullptr;
    }

    if (currentMap)
    {
        delete currentMap;
        currentMap = nullptr;
    }

    if (camera)
    {
        delete camera;
        camera = nullptr;
    }

    CloseWindow();
}

void GameManager::LoadLevel(const std::string &levelPath)
{
    if (currentMap)
    {
        delete currentMap;
    }

    currentMap = new TiledMap();
    currentMap->Load(levelPath);

    player->Init(currentMap->GetPlayerSpawn());
}
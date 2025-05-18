extern "C" {
#include "raylib.h"
}
#include "core/GameManager.h"

GameManager::GameManager()
    : screenWidth(800), screenHeight(600), gameTitle("Platforms"),
      currentState(GameState::PLAYING), currentMap(nullptr), player(nullptr),
      camera(nullptr), isRunning(true) {}

GameManager::~GameManager() { Shutdown(); }

void GameManager::Init(int width, int height, const std::string &title) {
  screenWidth = width;
  screenHeight = height;
  gameTitle = title;

  InitWindow(screenWidth, screenHeight, gameTitle.c_str());
  SetTargetFPS(60);

  currentMap = new TiledMap();
  player = new Player();

  SetLevel(1);

  score = 0;
  lives = 3;

  camera = new CameraController();
  camera->Init(static_cast<float>(screenWidth),
               static_cast<float>(screenHeight));

  for (const auto &coinSpawn : currentMap->GetCoinSpawnPoints()) {
    auto coin = std::make_unique<Coin>();
    coin->Init(coinSpawn);
    coins.push_back(std::move(coin));
  }

  isRunning = true;
};

void GameManager::Run() {
  while (isRunning && !WindowShouldClose()) {
    float deltaTime = GetFrameTime();
    HandleInput();
    Update(deltaTime);
    Draw();
  }
};

void GameManager::HandleInput() {
  if (IsKeyPressed(KEY_P)) {
    if (currentState == GameState::PLAYING) {
      currentState = GameState::PAUSED;
    } else if (currentState == GameState::PAUSED) {
      currentState = GameState::PLAYING;
    }
  }
}

void GameManager::Update(float deltaTime) {
  if (currentState != GameState::PLAYING) {
    return;
  }

  player->Update(currentMap, deltaTime);
  camera->Update(player->GetPosition());

  CheckCoinCollisions();

  for (auto &coin : coins) {
    coin->Update(deltaTime);
  }
};

void GameManager::Draw() {
  BeginDrawing();
  ClearBackground(BLACK);

  if (currentState == GameState::PLAYING || currentState == GameState::PAUSED) {
    camera->Begin();
    currentMap->Draw();
    player->Draw();

    for (const auto &coin : coins) {
      coin->Draw();
    }

    camera->End();

    if (currentState == GameState::PAUSED) {
      DrawRectangle(0, 0, screenWidth, screenHeight, ColorAlpha(BLACK, 0.5f));
      DrawText("PAUSED", screenWidth / 2 - MeasureText("PAUSED", 40) / 2,
               screenHeight / 2 - 40, 40, RAYWHITE);
    }
  }

  EndDrawing();
}

void GameManager::Shutdown() {
  if (player) {
    delete player;
    player = nullptr;
  }

  if (currentMap) {
    delete currentMap;
    currentMap = nullptr;
  }

  if (camera) {
    delete camera;
    camera = nullptr;
  }

  CloseWindow();
}

void GameManager::LoadLevel(const std::string &levelPath) {
  if (currentMap) {
    delete currentMap;
  }

  currentMap = new TiledMap();
  currentMap->Load(levelPath);

  player->Init(currentMap->GetPlayerSpawn());
}

void GameManager::AddScore(int points) { score += points; }

int GameManager::GetScore() const { return score; }

void GameManager::AddLives(int lives) { this->lives += lives; }

int GameManager::GetLives() const { return lives; }

void GameManager::RemoveLives(int lives) {
  this->lives -= lives;
  if (this->lives <= 0) {
    currentState = GameState::GAME_OVER;
  }
}

int GameManager::GetLevel() const { return level; }

void GameManager::SetLevel(int level) {
  this->level = level;
  std::string levelPath =
      "assets/tiled/levels/level" + std::to_string(level) + ".tmx";
  LoadLevel(levelPath);
}

void GameManager::CheckCoinCollisions() {
  const Rectangle playerRect = player->GetCollisionRect();

  auto coinIt = coins.begin();
  while (coinIt != coins.end()) {
    const Rectangle coinRect = (*coinIt)->GetCollisionRect();

    if (CheckCollisionRecs(playerRect, coinRect)) {
      AddScore((*coinIt)->GetValue());
      coinIt = coins.erase(coinIt);
    } else {
      ++coinIt;
    }
  }
}

#include "camera/CameraController.h"
#include "objects/Coin.h"
#include "objects/Hud.h"
#include "objects/Player.h"
#include "tiled/TiledMap.h"
#include <memory>
#include <string>

enum class GameState { MAIN_MENU, PLAYING, PAUSED, GAME_OVER };

class GameManager {
public:
  GameManager();
  ~GameManager();

  void Init(int screenWidth, int screenHeight, const std::string &gameTitle);
  void Run();
  void Shutdown();
  void AddScore(int points);
  int GetScore() const;
  void AddLives(int lives);
  void RemoveLives(int lives);
  int GetLives() const;
  void SetLevel(int level);
  int GetLevel() const;

private:
  void HandleInput();
  void Update(float deltaTime);
  void Draw();
  void LoadLevel(const std::string &levelPath);
  void CheckCoinCollisions();
  void CheckIfPlayerFellOffPlatforms();

  int screenWidth;
  int screenHeight;
  std::string gameTitle;
  GameState currentState;
  int score = 0;
  int lives = 3;
  int level = 1;

  TiledMap *currentMap;
  Player *player;
  CameraController *camera;
  std::vector<std::unique_ptr<Coin>> coins;
  Hud hud;

  bool isRunning;
};

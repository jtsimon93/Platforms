#include <string>
#include <memory>
#include "tiled/TiledMap.h"
#include "camera/CameraController.h"
#include "objects/Player.h"
#include "objects/Coin.h"

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

    bool isRunning;
};

extern "C"
{
#include "raylib.h"
}
#include "core/GameManager.h"

int main()
{
    GameManager game;
    game.Init(800, 600, "Platforms");
    game.Run();
    return 0;
}
#pragma once

extern "C"
{
#include "raylib.h"
}
#include <string>
#include <vector>

struct Tileset
{
    int firstGid;
    int tileWidth;
    int tileHeight;
    int columns;
    Texture2D texture;
};

struct TileLayer
{
    std::string name;
    int width;
    int height;
    std::vector<int> data;
};

class TiledMap
{
public:
    ~TiledMap();
    bool Load(const std::string &filePath);
    void Draw() const;
    Vector2 GetPlayerSpawn() const;
    std::vector<Vector2> GetCoinSpawnPoints() const;
    bool IsTileSolid(Vector2 position) const;

private:
    int tileWidth = 0;
    int tileHeight = 0;
    int mapWidth = 0;
    int mapHeight = 0;

    Vector2 playerSpawn = {0, 0};
    std::vector<Vector2> coinSpawnPoints;
    std::vector<Tileset> tilesets;
    std::vector<TileLayer> layers;

    const Tileset *GetTilesetForGID(int gid) const;
    static Rectangle GetSourceRectForGID(int gid, const Tileset &tileset);
};

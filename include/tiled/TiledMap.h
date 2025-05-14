#pragma once

extern "C"
{
#include "raylib.h"
}
#include "tinyxml2.h"
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

private:
    int tileWidth = 0;
    int tileHeight = 0;
    int mapWidth = 0;
    int mapHeight = 0;

    Vector2 playerSpawn = {0, 0};
    std::vector<Tileset> tilesets;
    std::vector<TileLayer> layers;

    const Tileset *GetTilesetForGID(int gid) const;
    Rectangle GetSourceRectForGID(int gid, const Tileset &tileset) const;
};

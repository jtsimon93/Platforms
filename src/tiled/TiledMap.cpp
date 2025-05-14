#include "tiled/TiledMap.h"
#include <iostream>
#include <sstream>
#include <filesystem>

TiledMap::~TiledMap()
{
    for (auto &ts : tilesets)
    {
        UnloadTexture(ts.texture);
    }
}

bool TiledMap::Load(const std::string &filePath)
{
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(filePath.c_str()) != tinyxml2::XML_SUCCESS)
    {
        std::cerr << "Failed to load TMX file: " << filePath << std::endl;
        return false;
    }

    std::filesystem::path basePath = std::filesystem::path(filePath).parent_path();

    tinyxml2::XMLElement *map = doc.FirstChildElement("map");
    tileWidth = map->IntAttribute("tilewidth");
    tileHeight = map->IntAttribute("tileheight");
    mapWidth = map->IntAttribute("width");
    mapHeight = map->IntAttribute("height");

    // Load all tilesets
    for (tinyxml2::XMLElement *ts = map->FirstChildElement("tileset"); ts; ts = ts->NextSiblingElement("tileset"))
    {
        int firstGid = ts->IntAttribute("firstgid");
        const char *source = ts->Attribute("source");
        if (!source)
            continue;

        std::filesystem::path tsxPath = basePath / source;

        tinyxml2::XMLDocument tsxDoc;
        if (tsxDoc.LoadFile(tsxPath.string().c_str()) != tinyxml2::XML_SUCCESS)
        {
            std::cerr << "Failed to load TSX file: " << tsxPath << std::endl;
            continue;
        }

        tinyxml2::XMLElement *tsxRoot = tsxDoc.FirstChildElement("tileset");
        const char *imageSource = tsxRoot->FirstChildElement("image")->Attribute("source");

        Tileset tileset;
        tileset.firstGid = firstGid;
        tileset.tileWidth = tsxRoot->IntAttribute("tilewidth");
        tileset.tileHeight = tsxRoot->IntAttribute("tileheight");

        std::filesystem::path imagePath = tsxPath.parent_path() / imageSource;
        tileset.texture = LoadTexture(imagePath.string().c_str());
        tileset.columns = tileset.texture.width / tileset.tileWidth;

        tilesets.push_back(tileset);
    }

    // Load all tile layers
    for (tinyxml2::XMLElement *layer = map->FirstChildElement("layer"); layer; layer = layer->NextSiblingElement("layer"))
    {
        const char *layerName = layer->Attribute("name");
        if (!layerName)
            continue;

        TileLayer tileLayer;
        tileLayer.name = layerName;
        tileLayer.width = layer->IntAttribute("width");
        tileLayer.height = layer->IntAttribute("height");

        tinyxml2::XMLElement *data = layer->FirstChildElement("data");
        const char *csv = data->GetText();
        std::stringstream ss(csv);
        std::string item;
        while (std::getline(ss, item, ','))
        {
            tileLayer.data.push_back(std::stoi(item));
        }

        layers.push_back(tileLayer);
    }

    // Handle object groups
    // Note: Right now this only handles the PLAYER spawn point
    for (tinyxml2::XMLElement *objectGroup = map->FirstChildElement("objectgroup"); objectGroup; objectGroup = objectGroup->NextSiblingElement("objectgroup"))
    {
        for (tinyxml2::XMLElement *obj = objectGroup->FirstChildElement("object"); obj; obj = obj->NextSiblingElement("object"))
        {
            const char *name = obj->Attribute("name");
            if (name && std::string(name) == "Player")
            {
                float x = obj->FloatAttribute("x");
                float y = obj->FloatAttribute("y");
                playerSpawn = {x, y};
            }
        }
    }

    return true;
}

void TiledMap::Draw() const
{
    for (const auto &layer : layers)
    {
        for (int y = 0; y < layer.height; ++y)
        {
            for (int x = 0; x < layer.width; ++x)
            {
                int i = y * layer.width + x;
                int gid = layer.data[i];
                if (gid == 0)
                    continue;

                const Tileset *tileset = GetTilesetForGID(gid);
                if (!tileset)
                    continue;

                Rectangle src = GetSourceRectForGID(gid - tileset->firstGid, *tileset);
                Vector2 dest = {(float)(x * tileWidth), (float)(y * tileHeight)};

                DrawTextureRec(tileset->texture, src, dest, WHITE);
            }
        }
    }
}

const Tileset *TiledMap::GetTilesetForGID(int gid) const
{
    const Tileset *result = nullptr;
    for (const auto &ts : tilesets)
    {
        if (gid >= ts.firstGid)
            result = &ts;
        else
            break;
    }
    return result;
}

Rectangle TiledMap::GetSourceRectForGID(int gid, const Tileset &tileset) const
{
    int x = (gid % tileset.columns) * tileset.tileWidth;
    int y = (gid / tileset.columns) * tileset.tileHeight;
    return {(float)x, (float)y, (float)tileset.tileWidth, (float)tileset.tileHeight};
}

Vector2 TiledMap::GetPlayerSpawn() const
{
    return playerSpawn;
}

bool TiledMap::IsTileSolid(Vector2 position) const
{
    int tileX = (int)(position.x / tileWidth);
    int tileY = (int)(position.y / tileHeight);

    for (const auto &layer : layers)
    {
        if (layer.name != "platforms")
            continue;

        int index = tileY * layer.width + tileX;
        if (index < 0 || index >= layer.data.size())
            return false;

        return layer.data[index] != 0; // GID 0 means no tile
    }

    return false;
}

#include "TileMap.h"
#include "GameObject.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

TileMap::TileMap(GameObject& associated, const std::string& file, TileSet* tileSet)
    : Component(associated), tileSet(tileSet) {
    Load(file);
}

void TileMap::Load(const std::string& file) {
    std::ifstream stream(file);
    if (!stream.is_open()) {
        throw std::runtime_error("TileMap: Failed to open map file.");
    }

    stream >> mapWidth >> mapHeight >> mapDepth;
    tileMatrix.clear();

    int tile;
    while (stream >> tile) {
        tileMatrix.push_back(tile - 1);  // convert from 1-based to 0-based indexing
    }

    stream.close();
}

void TileMap::SetTileSet(TileSet* tileSet) {
    this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z) {
    int index = x + (y * mapWidth) + (z * mapWidth * mapHeight);
    return tileMatrix[index];
}

void TileMap::Render() {
    for (int z = 0; z < mapDepth; z++) {
        RenderLayer(z);
    }
}

void TileMap::RenderLayer(int layer) {
    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            int tile = At(x, y, layer);
            if (tile >= 0) {
                tileSet->RenderTile(tile, associated.box.x + x * tileSet->GetTileWidth(),
                                           associated.box.y + y * tileSet->GetTileHeight());
            }
        }
    }
}

void TileMap::Update(float dt){}

int TileMap::GetWidth() const { return mapWidth; }
int TileMap::GetHeight() const { return mapHeight; }
int TileMap::GetDepth() const { return mapDepth; }

bool TileMap::Is(std::string type) {
    return type == "TileMap";
}

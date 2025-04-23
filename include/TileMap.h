#ifndef TILEMAP_H
#define TILEMAP_H

#include "Component.h"
#include "TileSet.h"
#include <vector>
#include <string>
#include <memory>

class TileMap : public Component {
public:
    TileMap(GameObject& associated, const std::string& file, TileSet* tileSet);
    
    void Load(const std::string& file);
    void SetTileSet(TileSet* tileSet);
    int& At(int x, int y, int z = 0);

    void Render() override;
    void RenderLayer(int layer);
    bool Is(std::string type) override;
    void Update(float dt) override;

    int GetWidth() const;
    int GetHeight() const;
    int GetDepth() const;

private:
    std::vector<int> tileMatrix;
    TileSet* tileSet;
    int mapWidth, mapHeight, mapDepth;
};

#endif

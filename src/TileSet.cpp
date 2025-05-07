#include "TileSet.h"
#include <stdexcept>

TileSet::TileSet(int tileWidth, int tileHeight, const std::string& file)
    : tileSet(file, 1,1), tileWidth(tileWidth), tileHeight(tileHeight) {

    if (!tileSet.IsOpen())
        throw std::runtime_error("Failed to load tileSet.");

    int imageW = tileSet.GetWidth();
    int imageH = tileSet.GetHeight();
    columns = imageW / tileWidth;
    int rows = imageH / tileHeight;
    tileCount = columns * rows;
}



void TileSet::RenderTile(unsigned index, float x, float y) {
    if (index >= (unsigned)tileCount) return;

    int row = index / columns;
    int col = index % columns;

    tileSet.SetClip(col * tileWidth, row * tileHeight, tileWidth, tileHeight);
    tileSet.Render(x, y);
}

bool TileSet::IsOpen(){
    return tileSet.IsOpen();
}
int TileSet::GetTileWidth() const { return tileWidth; }
int TileSet::GetTileHeight() const { return tileHeight; }

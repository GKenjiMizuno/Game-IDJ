#ifndef SPRITE_H
#define SPRITE_H

#include "SDL_include.h"
#include <string>

class Sprite {
private:
    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;
    int frameCountW;
    int frameCountH;
    int frameWidth;
    int frameHeight;

public:
    Sprite();
    Sprite(string file);
    Sprite(string file, int frameCountW = 1, int frameCountH = 1);
    ~Sprite();
    void Open(string file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    void SetFrame(int frame);
    void SetFrameCount(int frameCountW, int frameCountH);
};

#endif
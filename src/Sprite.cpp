#include "Sprite.h"
#include "Game.h"

Sprite::Sprite() : texture(nullptr) {}

Sprite::Sprite(string file) : texture(nullptr) {
    Open(file);
}

Sprite::Sprite(std::string file, int frameCountW, int frameCountH) : texture(nullptr) {
    Open(file);
    SetFrameCount(frameCountW, frameCountH);
}


Sprite::~Sprite() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(string file) {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }

    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if (texture == nullptr) {
        cerr << "IMG_LoadTexture Error: " << SDL_GetError() << endl;
        exit(1);
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y) {
    SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = width;  
    dstrect.h = height;   
    
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect);
}

void Sprite::SetFrameCount(int frameCountW, int frameCountH) {
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
    frameWidth = width / frameCountW;
    frameHeight = height / frameCountH;
}

void Sprite::SetFrame(int frame) {
    int frameX = (frame % frameCountW) * (width / frameCountW);
    int frameY = (frame / frameCountW) * (height / frameCountH);
    
    SetClip(frameX, frameY, width/frameCountW, height/frameCountH);
}

int Sprite::GetWidth(){ 
    return width;
 }
int Sprite::GetHeight(){
     return height; 
    }
bool Sprite::IsOpen(){ 
    return texture != nullptr; 
}
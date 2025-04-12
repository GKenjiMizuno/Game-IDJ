#include "SpriteRenderer.h"
#include "GameObject.h"

SpriteRenderer::SpriteRenderer(GameObject& associated) : 
    Component(associated), sprite() {}

SpriteRenderer::SpriteRenderer(GameObject& associated, std::string file, int frameCountW, int frameCountH) : 
    Component(associated), sprite(file, frameCountW, frameCountH) {
    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();sprite.SetFrame(0);
}

void SpriteRenderer::Open(std::string file) {
    sprite.Open(file);
    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();
    sprite.SetFrame(0);
}

void SpriteRenderer::SetFrameCount(int frameCountW, int frameCountH) {
    sprite.SetFrameCount(frameCountW, frameCountH);
    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();
}


void SpriteRenderer::Update(float dt) {}

void SpriteRenderer::Render() {
    sprite.Render(associated.box.x, associated.box.y);
}

bool SpriteRenderer::Is(std::string type) {
    return type == "SpriteRenderer";
}

void SpriteRenderer::SetFrame(int frame) {
    sprite.SetFrame(frame);
}
// SpriteRenderer.cpp
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Camera.h"

SpriteRenderer::SpriteRenderer(GameObject& associated)
    : Component(associated), sprite() {}

SpriteRenderer::SpriteRenderer(GameObject& associated, std::string file, int frameCountW, int frameCountH)
    : Component(associated), sprite(file, frameCountW, frameCountH) {
    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();
    sprite.SetFrame(0);
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

void SpriteRenderer::SetFrame(int frame) {
    sprite.SetFrame(frame);
}

void SpriteRenderer::Update(float dt) {}

void SpriteRenderer::Render() {
    float x = associated.box.x;
    float y = associated.box.y;

    if (!cameraFollower) {
        x -= Camera::pos.x;
        y -= Camera::pos.y;
    }

    sprite.Render(x, y);
}

bool SpriteRenderer::Is(std::string type) {
    return type == "SpriteRenderer";
}

bool SpriteRenderer::IsOpen() {
    return sprite.IsOpen();
}

void SpriteRenderer::SetCameraFollower(bool enabled) {
    cameraFollower = enabled;
}

bool SpriteRenderer::IsCameraFollower() {
    return cameraFollower;
}


#include "Camera.h"
#include "InputManager.h"

Vec2 Camera::pos = Vec2();
Vec2 Camera::speed = Vec2();
GameObject* Camera::focus = nullptr;

void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {
    if (focus) {
        Camera::pos = focus->box.Center() - Vec2(600, 450);
    } else {
        speed = Vec2();
        if (InputManager::GetInstance().IsKeyDown(SDLK_LEFT))  speed.x = -200;
        if (InputManager::GetInstance().IsKeyDown(SDLK_RIGHT)) speed.x =  200;
        if (InputManager::GetInstance().IsKeyDown(SDLK_UP))    speed.y = -200;
        if (InputManager::GetInstance().IsKeyDown(SDLK_DOWN))  speed.y =  200;

        pos = pos + speed * dt;
    }
}  

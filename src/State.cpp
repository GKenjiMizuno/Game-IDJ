#include "State.h"

State::State() : quitRequested(false) {
    LoadAssets();
    music.Play();
}

void State::LoadAssets() {
    bg.Open("resources/img/Background.png");
    music.Open("resources/audio/BGM.wav");
}

void State::Update(float dt) {
    if (SDL_QuitRequested()) {
        quitRequested = true;
    }
}

void State::Render() {
    bg.Render(0, 0);
}

bool State::QuitRequested() {
    return quitRequested;
}
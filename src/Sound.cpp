#include "Sound.h"
#include "Resources.h"

Sound::Sound(GameObject& associated) : Component(associated), chunk(nullptr), channel(-1) {}

Sound::Sound(GameObject& associated, const std::string& file)
    : Sound(associated) {
    Open(file);
}

Sound::~Sound() {
    if (chunk) {
        Stop();
    }
}

void Sound::Open(const std::string& file) {
    chunk = Resources::GetSound(file);
    if (!chunk) {
        SDL_Log("Failed to load sound: %s", SDL_GetError());
    }
}

void Sound::Play(int times) {
    if (chunk) {
        channel = Mix_PlayChannel(-1, chunk, times - 1);
    }
}

void Sound::Stop() {
    if (chunk && channel != -1) {
        Mix_HaltChannel(channel);
    }
}

bool Sound::IsOpen() {
    return chunk != nullptr;
}

void Sound::Update(float dt) {
    // não faz nada por enquanto
}

void Sound::Render() {
    // som não renderiza
}

bool Sound::Is(std::string type) {
    return type == "Sound";
}

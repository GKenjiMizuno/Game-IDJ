#include "Music.h"

Music::Music() : music(nullptr) {}

Music::Music(string file) : music(nullptr) {
    Open(file);
}

Music::~Music() {
    Stop();
    if (music != nullptr) {
        Mix_FreeMusic(music);
    }
}

void Music::Play(int times) {
    if (music != nullptr) {
        Mix_PlayMusic(music, times);
    }
}

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file) {
    music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) {
        cerr << "Mix_LoadMUS Error: " << Mix_GetError() << std::endl;
        exit(1);
    }
}

bool Music::IsOpen() {
    return music != nullptr;
}
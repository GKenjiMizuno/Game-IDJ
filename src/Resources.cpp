#include "Resources.h"
#include "Game.h"  // Para acessar GetRenderer()
#include <SDL2/SDL_image.h>

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(const std::string& file) {
    auto it = imageTable.find(file);
    if (it != imageTable.end()) {
        return it->second;
    }

    SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if (texture) {
        imageTable[file] = texture;
    } else {
        SDL_Log("IMG_LoadTexture failed: %s", SDL_GetError());
    }
    return texture;
}

void Resources::ClearImages() {
    for (auto& pair : imageTable) {
        SDL_DestroyTexture(pair.second);
    }
    imageTable.clear();
}

Mix_Music* Resources::GetMusic(const std::string& file) {
    auto it = musicTable.find(file);
    if (it != musicTable.end()) {
        return it->second;
    }

    Mix_Music* music = Mix_LoadMUS(file.c_str());
    if (music) {
        musicTable[file] = music;
    } else {
        SDL_Log("Mix_LoadMUS failed: %s", SDL_GetError());
    }
    return music;
}

void Resources::ClearMusics() {
    for (auto& pair : musicTable) {
        Mix_FreeMusic(pair.second);
    }
    musicTable.clear();
}

Mix_Chunk* Resources::GetSound(const std::string& file) {
    auto it = soundTable.find(file);
    if (it != soundTable.end()) {
        return it->second;
    }

    Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
    if (chunk) {
        soundTable[file] = chunk;
    } else {
        SDL_Log("Mix_LoadWAV failed: %s", SDL_GetError());
    }
    return chunk;
}

void Resources::ClearSounds() {
    for (auto& pair : soundTable) {
        Mix_FreeChunk(pair.second);
    }
    soundTable.clear();
}

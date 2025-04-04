#include "Game.h"

Game* Game::instance = nullptr;

Game::Game(string title, int width, int height) {
    if (instance != nullptr) {
        cerr << "Erro: Jogo já instanciado!" << endl;
        exit(1);
    }
    instance = this;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        cerr << "Init Error: " << SDL_GetError() << endl;
        exit(1);
    }

    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
    if (IMG_Init(imgFlags) != imgFlags) {
        cerr << "Image Error: " << IMG_GetError() << endl;
        exit(1);
    }

    if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG) == 0) {
        cerr << "Mixer Error: " << Mix_GetError() << endl;
        exit(1);
    }
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
        cerr << "Audio Error: " << Mix_GetError() << endl;
        exit(1);
    }
    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window == nullptr) {
        cerr << "Window Error: " << SDL_GetError() << endl;
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        cerr << "Renderer Error: " << SDL_GetError() << endl;
        exit(1);
    }

    state = new State();
}

Game::~Game() {
    delete state;
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

Game& Game::GetInstance() {
    if (instance == nullptr) {
        new Game("Jogo Zumbi", 1200, 900);
    }
    return *instance;
}

void Game::Run() {
    while (!state->QuitRequested()) {
        state->Update(0);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33); 
    }
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

State& Game::GetState() {
    return *state;
}
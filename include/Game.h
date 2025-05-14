#ifndef GAME_H
#define GAME_H

#include "SDL_include.h"
#include "State.h"

class Game {
private:
    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;

    Game(std::string title, int width, int height);

    int frameStart;
    float dt;

public:
    ~Game();
    static Game& GetInstance();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();

    void CalculateDeltaTime();
    float GetDeltaTime();
};

#endif

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

    Game(string title, int width, int height);
    
public:
    ~Game();
    static Game& GetInstance();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
};

#endif
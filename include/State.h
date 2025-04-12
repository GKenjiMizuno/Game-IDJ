#ifndef STATE_H
#define STATE_H
#include <vector>
#include <memory>
#include "SDL_include.h"
#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"
using namespace std;

class State {
private:
    Sprite bg;
    Music music;
    bool quitRequested;
    vector<unique_ptr<GameObject>> objectArray;

public:
    State();
    virtual ~State() = default;
    bool QuitRequested();
    virtual void LoadAssets();
    virtual void Update(float dt);
    virtual void Render();
    void AddObject(GameObject* go);

};

#endif
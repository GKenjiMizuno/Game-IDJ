#include "State.h"
#include "Game.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "Animator.h"
#include "Animation.h"
#include <SDL_include.h>
#include <algorithm>
using namespace std;

State::State() : quitRequested(false) {
    LoadAssets();

    GameObject* bgGo = new GameObject();
    bgGo->AddComponent(new SpriteRenderer(*bgGo, "resources/img/Background.png"));
    AddObject(bgGo);

    GameObject* zombieGo = new GameObject();
    zombieGo->box.x = 600;
    zombieGo->box.y = 450;
    
    SpriteRenderer* zombieRenderer = new SpriteRenderer(*zombieGo, "resources/img/Enemy.png", 3, 2);
    zombieGo->AddComponent(zombieRenderer);
    
    Animator* zombieAnimator = new Animator(*zombieGo);
    zombieAnimator->AddAnimation("walking", Animation(0, 3, 0.1f));
    zombieAnimator->AddAnimation("dead", Animation(5, 5, 0));
    zombieAnimator->SetAnimation("walking");
    zombieGo->AddComponent(zombieAnimator);
    
    zombieGo->AddComponent(new Zombie(*zombieGo));
    AddObject(zombieGo);
    


}



void State::LoadAssets() {
    //bg.Open("resources/img/Background.png");
    music.Open("resources/audio/BGM.wav");
}

void State::Update(float dt) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quitRequested = true;
        }
    }

    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    objectArray.erase(
        remove_if(
            objectArray.begin(), 
            objectArray.end(),
            [](const unique_ptr<GameObject>& go) {
                return go->IsDead();
            }
        ),
        objectArray.end()
    );
}

void State::Render() {
    for (auto& go : objectArray) {
        go->Render();
    }
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::AddObject(GameObject* go) {
    objectArray.emplace_back(go);
}
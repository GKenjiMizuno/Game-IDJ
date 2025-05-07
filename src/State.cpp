#include "State.h"
#include "Game.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "Animator.h"
#include "Animation.h"
#include "TileSet.h"
#include "TileMap.h"
#include <SDL_include.h>
#include <algorithm>
#include <iostream> // Para debug

using namespace std;

State::State() : quitRequested(false) {
    LoadAssets();

    // 🖼️ BACKGROUND
    GameObject* bgGo = new GameObject();
    SpriteRenderer* bgSprite = new SpriteRenderer(*bgGo, "resources/img/Background.png");
    if (!bgSprite->IsOpen()) {
        cerr << "Erro ao carregar Background.png: " << SDL_GetError() << endl;
    }
    bgGo->AddComponent(bgSprite);
    AddObject(bgGo);

    // ⬛ TILEMAP
    GameObject* tilemapGo = new GameObject();
    tilemapGo->box.x = 0;
    tilemapGo->box.y = 0;
    tilemapGo->box.w = 0; // Pode ser ajustado com base no tileset
    tilemapGo->box.h = 0;

    TileSet* tileSet = new TileSet(64, 64, "resources/img/Tileset.png");
    if (!tileSet->IsOpen()) {
        cerr << "Erro ao carregar Tileset.png: " << SDL_GetError() << endl;
    }

    TileMap* tileMap = new TileMap(*tilemapGo, "resources/map/map.txt", tileSet);
    tilemapGo->AddComponent(tileMap);
    AddObject(tilemapGo);


    // 🧟 ZOMBIE
    GameObject* zombieGo = new GameObject();
    zombieGo->box.x = 600;
    zombieGo->box.y = 450;

    SpriteRenderer* zombieRenderer = new SpriteRenderer(*zombieGo, "resources/img/Enemy.png", 3, 2);
    if (!zombieRenderer->IsOpen()) {
        cerr << "Erro ao carregar Enemy.png: " << SDL_GetError() << endl;
    }
    zombieGo->AddComponent(zombieRenderer);

    Animator* zombieAnimator = new Animator(*zombieGo);
    zombieAnimator->AddAnimation("walking", Animation(0, 3, 0.1f));
    zombieAnimator->AddAnimation("dead", Animation(5, 5, 0));
    zombieAnimator->SetAnimation("walking");
    zombieGo->AddComponent(zombieAnimator);

    Zombie* zombie = new Zombie(*zombieGo);
    zombieGo->AddComponent(zombie);

    AddObject(zombieGo);

    // ▶️ Música de fundo
    music.Play(-1); // Reproduz em loop
}

void State::LoadAssets() {
    music.Open("resources/audio/BGM.wav");
    if (!music.IsOpen()) {
        cerr << "Erro ao carregar BGM.wav: " << SDL_GetError() << endl;
    }
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

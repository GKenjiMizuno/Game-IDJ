#include "GameObject.h"
#include <algorithm>
using namespace std;

GameObject::GameObject() : isDead(false) {}

GameObject::~GameObject() {
    for (auto it = components.rbegin(); it != components.rend(); ++it) {
        delete *it;
    }
    components.clear();
}

void GameObject::Update(float dt) {
    for (auto& component : components) {
        component->Update(dt);
    }
}

void GameObject::Render() {
    for (auto& component : components) {
        component->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
    components.push_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt) {
    auto it = find(components.begin(), components.end(), cpt);
    if (it != components.end()) {
        delete *it; 
        components.erase(it);
    }
}

Component* GameObject::GetComponent(string type) {
    for (auto& component : components) {
        if (component->Is(type)) {
            return component;
        }
    }
    return nullptr;
}
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <vector>
#include <memory>
#include "Component.h"
#include "Rect.h"
using namespace std;

class GameObject {

    private:
        vector<Component*> components;
        bool isDead;

    public:
        Rect box;
        GameObject();
        ~GameObject();
        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);
        Component* GetComponent(string type);
};

#endif
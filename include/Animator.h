#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "Component.h"
#include "Animation.h"
#include "GameObject.h"
#include <unordered_map>
#include <string>
using namespace std;


class Animator : public Component {
private:
    unordered_map<string, Animation> animations;
    int frameStart;
    int frameEnd;
    float frameTime;
    int currentFrame;
    float timeElapsed;

public:
    Animator(GameObject& associated);
    
    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;
    void SetAnimation(string name);
    void AddAnimation(string name, Animation anim);
};

#endif
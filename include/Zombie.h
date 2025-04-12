#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "Component.h"
using namespace std;

class Zombie : public Component {
private:
    int hitpoints;

public:
    Zombie(GameObject& associated);
    
    void Damage(int damage);
    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;
};

#endif
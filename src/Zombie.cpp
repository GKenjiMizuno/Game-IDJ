#include "Zombie.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include <string>

Zombie::Zombie(GameObject& associated) : 
    Component(associated), 
    hitpoints(100) 
{
    SpriteRenderer* renderer = new SpriteRenderer(associated,"resources/img/Enemy.png",3,2   );
    associated.AddComponent(renderer);

    Animator* animator = new Animator(associated);
    animator->AddAnimation("walking", Animation(0, 3, 0.1f));
    animator->AddAnimation("dead", Animation(5, 5, 0));       
    animator->SetAnimation("walking");
    associated.AddComponent(animator);
}

void Zombie::Damage(int damage) {
    hitpoints -= damage;
    if (hitpoints <= 0) {
        Animator* animator = (Animator*)associated.GetComponent("Animator");
        if (animator) {
            animator->SetAnimation("dead");
        }
    }
}

void Zombie::Update(float dt) {
    if (hitpoints <= 0) return;
    
    Damage(1);
    
    Animator* animator = (Animator*)associated.GetComponent("Animator");
    if (animator) {
        animator->Update(dt);
    }
}

void Zombie::Render() {
}

bool Zombie::Is(std::string type) {
    return type == "Zombie";
}
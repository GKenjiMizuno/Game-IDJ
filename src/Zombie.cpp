#include "Zombie.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Animation.h"

Zombie::Zombie(GameObject& associated)
    : Component(associated), hitpoints(100), deathSound(associated, "resources/audio/Dead.wav") {


}

void Zombie::Damage(int damage) {
    hitpoints -= damage;

    if (hitpoints <= 0) {
        // Tocar som da morte
        if (deathSound.IsOpen()) {
            deathSound.Play(1);
        }

        // Trocar animação para "dead"
        auto animator = (Animator*)associated.GetComponent("Animator");
        if (animator) {
            animator->SetAnimation("dead");
        }
    }
}

void Zombie::Update(float dt) {
    Damage(1); // temporário: perde 1 HP por frame
}

void Zombie::Render() {
    // Nada aqui por enquanto
}

bool Zombie::Is(std::string type) {
    return type == "Zombie";
}

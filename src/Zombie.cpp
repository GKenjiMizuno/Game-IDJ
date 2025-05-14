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
    if (hitpoints > 0) {
        Damage(1);  // dano contínuo só para teste
    } else {
        if (!deadPlayed) {
            auto animator = (Animator*)associated.GetComponent("Animator");
            if (animator) {
                animator->SetAnimation("dead");
            }
            deathSound.Play();
            deathTimer.Restart();
            deadPlayed = true;
        } else if (deathTimer.Get() > 1.0f) {
            associated.RequestDelete();
        }
    }
}

void Zombie::Render() {
}

bool Zombie::Is(std::string type) {
    return type == "Zombie";
}

#include "Zombie.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Animation.h"

Zombie::Zombie(GameObject& associated)
    : Component(associated), hitpoints(100), deathSound(associated, "Recursos/audio/Dead.wav") {

    // SpriteRenderer com 3x2 frames (colunas x linhas)
    auto sprite = new SpriteRenderer(associated, "resources/img/Enemy.png", 3, 2);
    sprite->SetFrame(0);
    associated.AddComponent(sprite);

    // Animator com animações walking e dead
    auto animator = new Animator(associated);
    animator->AddAnimation("walking", Animation(0, 3, 10));
    animator->AddAnimation("dead", Animation(5, 5, 0));
    animator->SetAnimation("walking");
    associated.AddComponent(animator);
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

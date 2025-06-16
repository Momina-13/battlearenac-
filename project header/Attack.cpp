#include "Attack.h"
using namespace std;

Attack::Attack(int damage, HitBox hitbox)
    : damage(damage), hitbox(hitbox) {
}

bool Attack::performAttack(Character& defender) {
    if (hitbox.isColliding(defender.getHitBox())) {
        defender.takeDamage(damage);
        return true;
    }
    return false;
}
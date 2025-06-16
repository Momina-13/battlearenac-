#pragma once
#ifndef ATTACK_H
#define ATTACK_H

#include "HitBox.h"
#include "Character.h"

class Attack {
private:
    int damage;
    HitBox hitbox;

public:
    Attack(int damage, HitBox hitbox);
    bool performAttack(Character& defender);
};

#endif 
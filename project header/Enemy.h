#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Enemy : public Character {
private:
    int difficultyLevel;

public:
    Enemy(int difficultyLevel, int x, int y);
    int calculateAttackDamage(const Character& player) const;
    bool attack(Character& player);
    void save(const std::string& filename);
    void load(const std::string& filename);
};

#endif // ENEMY_H
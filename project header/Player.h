#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <string>

class Player : public Character {
private:
    std::string name;

public:
    Player(std::string name, int x, int y);
    int calculateAttackDamage(const Character& enemy) const;
    bool attack(Character& enemy);
    void save(const std::string& filename);
    void load(const std::string& filename);
};

#endif 
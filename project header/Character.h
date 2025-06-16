#ifndef CHARACTER_H
#define CHARACTER_H

#include "HitBox.h"
#include "Board.h"
#include <string>

class Character {
protected:
    int health, maxHealth;
    int x, y;
    HitBox hitbox;

public:
    Character(int maxHp, int x, int y, int r);
    virtual void takeDamage(int amount);
    void heal(int amount);
    bool isAlive() const;
    bool moveTo(int newX, int newY, Board& board);
    void moveTo(int newX, int newY);
    HitBox getHitBox() const;
    int getHealth() const;
    int getX() const;
    int getY() const;
    std::string getPosition() const;
    int getDistanceTo(const Character& other) const;
    int max(int a, int b) const;
    int min(int a, int b) const;
};

#endif 
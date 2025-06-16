#include "Character.h"
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

Character::Character(int maxHp, int x, int y, int r)
    : maxHealth(maxHp), health(maxHp), x(x), y(y), hitbox(x, y, r) {
}

void Character::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

void Character::heal(int amount) {
    health += amount;
    if (health > maxHealth) health = maxHealth;
}

bool Character::isAlive() const {
    return health > 0;
}

bool Character::moveTo(int newX, int newY, Board& board) {
    if (!board.isValidPosition(newX, newY)) {
        cout << "Invalid position! Must be within 0-9 range.\n";
        return false;
    }

    x = newX;
    y = newY;
    hitbox.setPosition(x, y);
    return true;
}

void Character::moveTo(int newX, int newY) {
    x = newX;
    y = newY;
    hitbox.setPosition(x, y);
}

HitBox Character::getHitBox() const {
    return hitbox;
}

int Character::getHealth() const {
    return health;
}

int Character::getX() const {
    return x;
}

int Character::getY() const {
    return y;
}

string Character::getPosition() const {
    ostringstream oss;
    oss << "(" << x << ", " << y << ")";
    return oss.str();
}

int Character::getDistanceTo(const Character& other) const {
    int dx = abs(x - other.x);
    int dy = abs(y - other.y);
    return (dx > dy) ? dx : dy;
}

int Character::max(int a, int b) const {
    return (a > b) ? a : b;
}

int Character::min(int a, int b) const {
    return (a < b) ? a : b;
}

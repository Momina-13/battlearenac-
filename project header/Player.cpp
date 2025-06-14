#include "Player.h"
#include <iostream>
#include <fstream>

Player::Player(std::string name, int x, int y)
    : Character(100, x, y, 10), name(name) {
}

int Player::calculateAttackDamage(const Character& enemy) const {
    int distance = getDistanceTo(enemy);
    if (distance == 0) return 0; // Can't attack if on same position

    // Base damage 20, reduced by distance
    int damage = 20 - (distance - 1) * 2;
    return max(damage, 5); // Minimum 5 damage
}

bool Player::attack(Character& enemy) {
    int distance = getDistanceTo(enemy);
    if (distance <= 3) { // Maximum attack range
        int damage = calculateAttackDamage(enemy);
        enemy.takeDamage(damage);
        std::cout << "Attack deals " << damage << " damage! (Distance: " << distance << ")\n";
        return true;
    }
    return false;
}

void Player::save(const std::string& filename) {
    std::ofstream out(filename.c_str());
    out << name << " " << health << " " << x << " " << y << std::endl;
}

void Player::load(const std::string& filename) {
    std::ifstream in(filename.c_str());
    in >> name >> health >> x >> y;
    hitbox.setPosition(x, y);
}
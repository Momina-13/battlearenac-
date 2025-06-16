#include "Enemy.h"
#include <iostream>
#include <fstream>

Enemy::Enemy(int difficultyLevel, int x, int y)
    : Character(100 + 50 * (difficultyLevel - 1), x, y, 10), difficultyLevel(difficultyLevel) {
}

int Enemy::calculateAttackDamage(const Character& player) const {
    int distance = getDistanceTo(player);
    if (distance == 0) return 0; 

 
    int damage = 15 - (distance - 1) * 2;
    return max(damage, 3); 
}

bool Enemy::attack(Character& player) {
    int distance = getDistanceTo(player);
    if (distance <= 3) { 
        int damage = calculateAttackDamage(player);
        player.takeDamage(damage);
        std::cout << "Enemy attack deals " << damage << " damage! (Distance: " << distance << ")\n";
        return true;
    }
    return false;
}

void Enemy::save(const std::string& filename) {
    std::ofstream out(filename.c_str());
    out << difficultyLevel << " " << health << " " << x << " " << y << std::endl;
}

void Enemy::load(const std::string& filename) {
    std::ifstream in(filename.c_str());
    in >> difficultyLevel >> health >> x >> y;
    hitbox.setPosition(x, y);
}
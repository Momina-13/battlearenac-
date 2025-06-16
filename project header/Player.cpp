#include "Player.h"
#include <iostream>
#include <fstream>

using namespace std;

Player::Player(string name, int x, int y)
    : Character(100, x, y, 10), name(name) {
}

int Player::calculateAttackDamage(const Character& enemy) const {
    int distance = getDistanceTo(enemy);
    if (distance == 0) return 0;

    int damage = 20 - (distance - 1) * 2;
    return max(damage, 5);
}

bool Player::attack(Character& enemy) {
    int distance = getDistanceTo(enemy);
    if (distance <= 3) {
        int damage = calculateAttackDamage(enemy);
        enemy.takeDamage(damage);
        cout << "Attack deals " << damage << " damage! (Distance: " << distance << ")\n";
        return true;
    }
    return false;
}

void Player::save(const string& filename) {
    ofstream out(filename.c_str());
    out << name << " " << health << " " << x << " " << y << endl;
}

void Player::load(const string& filename) {
    ifstream in(filename.c_str());
    in >> name >> health >> x >> y;
    hitbox.setPosition(x, y);
}

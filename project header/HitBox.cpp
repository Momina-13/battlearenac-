#include "HitBox.h"
#include <cmath>
using namespace std;

HitBox::HitBox(int x, int y, int r) : centerX(x), centerY(y), radius(r) {}

bool HitBox::isColliding(const HitBox& other) {
    int dx = centerX - other.centerX;
    int dy = centerY - other.centerY;
    double distance = sqrt(dx * dx + dy * dy);
    return distance <= (radius + other.radius);
}

void HitBox::setPosition(int x, int y) {
    centerX = x;
    centerY = y;
}

int HitBox::getX() const {
    return centerX;
}

int HitBox::getY() const {
    return centerY;
}

int HitBox::getRadius() const {
    return radius;
}
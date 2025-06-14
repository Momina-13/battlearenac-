#ifndef HITBOX_H
#define HITBOX_H

class HitBox {
private:
    int centerX, centerY, radius;

public:
    HitBox(int x = 0, int y = 0, int r = 10);
    bool isColliding(const HitBox& other);
    void setPosition(int x, int y);
    int getX() const;
    int getY() const;
    int getRadius() const;
};

#endif // HITBOX_H
#pragma once
#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"
#include "Enemy.h"
#include "Board.h"

class Level {
private:
    int levelNumber;
    Player& player;
    Enemy enemy;
    Board board;

public:
    Level(int levelNumber, Player& player);
    void ensureMinimumDistance();
    int getLevelNumber() const;
    Enemy& getEnemy();
    Board& getBoard();
    void initLevel();
    bool levelSuccess() const;
};

#endif 
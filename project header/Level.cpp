#include "Level.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Level::Level(int levelNumber, Player& player)
    : levelNumber(levelNumber), player(player), enemy(levelNumber, 5, 5), board() {
    ensureMinimumDistance();
}

void Level::ensureMinimumDistance() {
    while (player.getDistanceTo(enemy) < 2) {
        int newX = rand() % Board::getBoardSize();
        int newY = rand() % Board::getBoardSize();
        enemy.moveTo(newX, newY);
    }
}

int Level::getLevelNumber() const {
    return levelNumber;
}

Enemy& Level::getEnemy() {
    return enemy;
}

Board& Level::getBoard() {
    return board;
}

void Level::initLevel() {
    cout << "Level " << levelNumber << " Start!\n";
    board.displayBoard(player.getX(), player.getY(), enemy.getX(), enemy.getY());
}

bool Level::levelSuccess() const {
    return !enemy.isAlive();
}

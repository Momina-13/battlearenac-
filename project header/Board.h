#pragma once
#ifndef BOARD_H
#define BOARD_H

class Board {
private:
    static const int BOARD_SIZE = 10;
    static const int MAX_SPECIAL_BOXES = 10;
    char grid[BOARD_SIZE][BOARD_SIZE];
    int healthBoxX[MAX_SPECIAL_BOXES];
    int healthBoxY[MAX_SPECIAL_BOXES];
    int numHealthBoxes;
    int bombBoxX[MAX_SPECIAL_BOXES];
    int bombBoxY[MAX_SPECIAL_BOXES];
    int numBombBoxes;

public:
    Board();
    void generateHealthBoxes();
    void generateBombBoxes();
    void updateGrid();
    bool hasHealthBox(int x, int y) const;
    bool hasBombBox(int x, int y) const;
    bool isNearHealthBox(int x, int y) const;
    bool isOnBombBox(int x, int y) const;
    void removeHealthBox(int x, int y);
    void removeBombBox(int x, int y);
    void displayBoard(int playerX, int playerY, int enemyX, int enemyY) const;
    bool isValidPosition(int x, int y) const;
    static int getBoardSize();
};

#endif 
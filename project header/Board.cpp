#include "Board.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

Board::Board() : numHealthBoxes(0), numBombBoxes(0) {
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            grid[i][j] = '.';
        }
    }
    generateHealthBoxes();
    generateBombBoxes();
    updateGrid();
}

void Board::generateHealthBoxes() {
    numHealthBoxes = 0;
   
    int numBoxes = 3 + rand() % 3;
    for (int i = 0; i < numBoxes; i++) {
        int x, y;
        bool validPosition = false;
        int attempts = 0;
        while (!validPosition && attempts < 50) {
            x = rand() % BOARD_SIZE;
            y = rand() % BOARD_SIZE;
            if (!hasHealthBox(x, y) && !hasBombBox(x, y)) {
                validPosition = true;
            }
            attempts++;
        }
        if (validPosition && numHealthBoxes < MAX_SPECIAL_BOXES) {
            healthBoxX[numHealthBoxes] = x;
            healthBoxY[numHealthBoxes] = y;
            numHealthBoxes++;
        }
    }
}

void Board::generateBombBoxes() {
    numBombBoxes = 0;
   
    int numBoxes = 2 + rand() % 3;
    for (int i = 0; i < numBoxes; i++) {
        int x, y;
        bool validPosition = false;
        int attempts = 0;
        while (!validPosition && attempts < 50) {
            x = rand() % BOARD_SIZE;
            y = rand() % BOARD_SIZE;
            if (!hasHealthBox(x, y) && !hasBombBox(x, y)) {
                validPosition = true;
            }
            attempts++;
        }
        if (validPosition && numBombBoxes < MAX_SPECIAL_BOXES) {
            bombBoxX[numBombBoxes] = x;
            bombBoxY[numBombBoxes] = y;
            numBombBoxes++;
        }
    }
}

void Board::updateGrid() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            grid[i][j] = '.';
        }
    }

    for (int i = 0; i < numHealthBoxes; i++) {
        grid[healthBoxX[i]][healthBoxY[i]] = 'H';
    }

    for (int i = 0; i < numBombBoxes; i++) {
        grid[bombBoxX[i]][bombBoxY[i]] = 'B';
    }
}

bool Board::hasHealthBox(int x, int y) const {
    for (int i = 0; i < numHealthBoxes; i++) {
        if (healthBoxX[i] == x && healthBoxY[i] == y) return true;
    }
    return false;
}

bool Board::hasBombBox(int x, int y) const {
    for (int i = 0; i < numBombBoxes; i++) {
        if (bombBoxX[i] == x && bombBoxY[i] == y) return true;
    }
    return false;
}

bool Board::isNearHealthBox(int x, int y) const {
    for (int i = 0; i < numHealthBoxes; i++) {
        int dx = abs(x - healthBoxX[i]);
        int dy = abs(y - healthBoxY[i]);
        if (dx <= 1 && dy <= 1) return true;
    }
    return false;
}

bool Board::isOnBombBox(int x, int y) const {
    for (int i = 0; i < numBombBoxes; i++) {
        if (bombBoxX[i] == x && bombBoxY[i] == y) return true;
    }
    return false;
}

void Board::removeHealthBox(int x, int y) {
    for (int i = 0; i < numHealthBoxes; i++) {
        int dx = abs(x - healthBoxX[i]);
        int dy = abs(y - healthBoxY[i]);
        if (dx <= 1 && dy <= 1) {
            // Shift remaining boxes
            for (int j = i; j < numHealthBoxes - 1; j++) {
                healthBoxX[j] = healthBoxX[j + 1];
                healthBoxY[j] = healthBoxY[j + 1];
            }
            numHealthBoxes--;
            break;
        }
    }
    updateGrid();
}

void Board::removeBombBox(int x, int y) {
    for (int i = 0; i < numBombBoxes; i++) {
        if (bombBoxX[i] == x && bombBoxY[i] == y) {
            for (int j = i; j < numBombBoxes - 1; j++) {
                bombBoxX[j] = bombBoxX[j + 1];
                bombBoxY[j] = bombBoxY[j + 1];
            }
            numBombBoxes--;
            break;
        }
    }
    updateGrid();
}

void Board::displayBoard(int playerX, int playerY, int enemyX, int enemyY) const {
    cout << "\n=== GAME BOARD ===\n";
    cout << "  ";
    for (int j = 0; j < BOARD_SIZE; j++) {
        cout << j << " ";
    }
    cout << "\n";

    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (i == playerX && j == playerY) {
                cout << "P ";
            }
            else if (i == enemyX && j == enemyY) {
                cout << "E ";
            }
            else {
                cout << grid[i][j] << " ";
            }
        }
        cout << "\n";
    }
    cout << "Legend: P=Player, E=Enemy, H=Health+10, B=Bomb-10, .=Empty\n\n";
}

bool Board::isValidPosition(int x, int y) const {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

int Board::getBoardSize() {
    return BOARD_SIZE;
}
#include "Board.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

Board::Board() : numHealthBoxes(0), numBombBoxes(0) {
    // Initialize grid
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
    // Generate 3-5 random health boxes
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
    // Generate 2-4 random bomb boxes
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
    // Clear grid
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            grid[i][j] = '.';
        }
    }

    // Place health boxes
    for (int i = 0; i < numHealthBoxes; i++) {
        grid[healthBoxX[i]][healthBoxY[i]] = 'H';
    }

    // Place bomb boxes
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
            // Shift remaining boxes
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
    std::cout << "\n=== GAME BOARD ===\n";
    std::cout << "  ";
    for (int j = 0; j < BOARD_SIZE; j++) {
        std::cout << j << " ";
    }
    std::cout << "\n";

    for (int i = 0; i < BOARD_SIZE; i++) {
        std::cout << i << " ";
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (i == playerX && j == playerY) {
                std::cout << "P ";
            }
            else if (i == enemyX && j == enemyY) {
                std::cout << "E ";
            }
            else {
                std::cout << grid[i][j] << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "Legend: P=Player, E=Enemy, H=Health+10, B=Bomb-10, .=Empty\n\n";
}

bool Board::isValidPosition(int x, int y) const {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

int Board::getBoardSize() {
    return BOARD_SIZE;
}
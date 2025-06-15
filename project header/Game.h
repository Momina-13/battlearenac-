#ifndef GAME_H
#define GAME_H

#include <string>
#include "Board.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "Logger.h"
#include "Level.h"

class Game {
    Player player;
    Level* currentLevel;
    int currentLevelNumber;
    Logger logger;

public:
    Game();
    void loadGame();
    void saveGame();
    bool isValidMove(int newX, int newY, const Character& other);
    void processSpecialBoxes(Character& character, const std::string& characterName);
    void runLevel();
    void playerTurn();
    void enemyTurn();
    void nextLevel();
    bool isGameOver() const;
    void runGame();
    void showEnding();
};

#endif

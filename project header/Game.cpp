#include "Game.h"
#include "Utils.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Game::Game() : player("Hero", 0, 0), currentLevel(0), currentLevelNumber(1) {}

void Game::loadGame() {
    player.load("player_save.txt");
}

void Game::saveGame() {
    player.save("player_save.txt");
}

bool Game::isValidMove(int newX, int newY, const Character& other) {
    return currentLevel->getBoard().isValidPosition(newX, newY) &&
        !(newX == other.getX() && newY == other.getY());
}

void Game::processSpecialBoxes(Character& character, const std::string& characterName) {
    Board& board = currentLevel->getBoard();
    int x = character.getX();
    int y = character.getY();

    if (board.isNearHealthBox(x, y)) {
        character.heal(10);
        board.removeHealthBox(x, y);
        std::cout << characterName << " found a health box! +10 Health!\n";
        logger.logMessage(characterName + " gained 10 health from health box");
    }

    if (board.isOnBombBox(x, y)) {
        if (characterName == "Player") {
            currentLevel->getEnemy().takeDamage(10);
            std::cout << "Player stepped on a bomb! Enemy takes 10 damage!\n";
            logger.logMessage("Player stepped on bomb - Enemy took 10 damage");
        }
        else {
            player.takeDamage(10);
            std::cout << "Enemy stepped on a bomb! Player takes 10 damage!\n";
            logger.logMessage("Enemy stepped on bomb - Player took 10 damage");
        }
        board.removeBombBox(x, y);
    }
}

void Game::runLevel() {
    delete currentLevel;
    currentLevel = new Level(currentLevelNumber, player);
    currentLevel->initLevel();

    while (player.isAlive() && currentLevel->getEnemy().isAlive()) {
        std::cout << "\n--- Player Turn ---\n";
        playerTurn();

        if (!currentLevel->getEnemy().isAlive()) break;
        if (!player.isAlive()) break;

        std::cout << "\n--- Enemy Turn (Player 2) ---\n";
        enemyTurn();

        if (!player.isAlive()) break;
        if (!currentLevel->getEnemy().isAlive()) break;

        currentLevel->getBoard().displayBoard(
            player.getX(), player.getY(),
            currentLevel->getEnemy().getX(), currentLevel->getEnemy().getY()
        );

        std::cout << "Player Health: " << player.getHealth()
            << " | Enemy Health: " << currentLevel->getEnemy().getHealth() << "\n";

        logger.logMessage("Player Health: " + intToString(player.getHealth()) +
            " Enemy Health: " + intToString(currentLevel->getEnemy().getHealth()));
    }
}

void Game::playerTurn() {
    currentLevel->getBoard().displayBoard(
        player.getX(), player.getY(),
        currentLevel->getEnemy().getX(), currentLevel->getEnemy().getY()
    );

    std::cout << "Player Position: " << player.getPosition() << "\n";
    std::cout << "Enemy Position: " << currentLevel->getEnemy().getPosition() << "\n";

    bool validMove = false;
    while (!validMove) {
        int newX, newY;
        std::cout << "Enter new X coordinate (0-9): ";
        std::cin >> newX;
        std::cout << "Enter new Y coordinate (0-9): ";
        std::cin >> newY;

        if (isValidMove(newX, newY, currentLevel->getEnemy())) {
            Character tempPlayer = player;
            tempPlayer.moveTo(newX, newY);
            if (tempPlayer.getDistanceTo(currentLevel->getEnemy()) >= 2) {
                player.moveTo(newX, newY);
                validMove = true;
                processSpecialBoxes(player, "Player");
            }
            else {
                std::cout << "You must stay at least 2 blocks away from the enemy!\n";
            }
        }
        else {
            std::cout << "Invalid move! Position occupied or out of bounds.\n";
        }
    }

    char choice;
    std::cout << "Attack enemy? (y/n): ";
    std::cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        if (player.attack(currentLevel->getEnemy())) {
            std::cout << "Player hits Enemy!\n";
        }
        else {
            std::cout << "Enemy is too far away to attack! (Max range: 3 blocks)\n";
        }
    }
}

void Game::enemyTurn() {
    std::cout << "Enemy Position: " << currentLevel->getEnemy().getPosition() << "\n";
    std::cout << "Player Position: " << player.getPosition() << "\n";

    bool validMove = false;
    while (!validMove) {
        int newX, newY;
        std::cout << "Enter new X coordinate for Enemy (0-9): ";
        std::cin >> newX;
        std::cout << "Enter new Y coordinate for Enemy (0-9): ";
        std::cin >> newY;

        if (isValidMove(newX, newY, player)) {
            Character tempEnemy = currentLevel->getEnemy();
            tempEnemy.moveTo(newX, newY);
            if (tempEnemy.getDistanceTo(player) >= 2) {
                currentLevel->getEnemy().moveTo(newX, newY);
                validMove = true;
                processSpecialBoxes(currentLevel->getEnemy(), "Enemy");
            }
            else {
                std::cout << "Enemy must stay at least 2 blocks away from the player!\n";
            }
        }
        else {
            std::cout << "Invalid move! Position occupied or out of bounds.\n";
        }
    }

    char choice;
    std::cout << "Attack player? (y/n): ";
    std::cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        if (currentLevel->getEnemy().attack(player)) {
            std::cout << "Enemy hits Player!\n";
        }
        else {
            std::cout << "Player is too far away to attack! (Max range: 3 blocks)\n";
        }
    }
}

void Game::nextLevel() {
    currentLevelNumber++;
}

bool Game::isGameOver() const {
    return !player.isAlive() || currentLevelNumber > 2;
}

void Game::runGame() {
    logger.open("game_log.txt");

    while (!isGameOver()) {
        runLevel();
        if (currentLevel->levelSuccess()) {
            std::cout << "Level " << currentLevelNumber << " Cleared!\n";
            nextLevel();
        }
        else {
            break;
        }
    }

    showEnding();
    logger.close();
}

void Game::showEnding() {
    if (player.isAlive() && currentLevelNumber > 2) {
        std::cout << "Congratulations! You won the game!\n";
    }
    else {
        std::cout << "Game Over. Try Again!\n";
    }
}

#include "Game.h"
#include "Utils.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

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

void Game::processSpecialBoxes(Character& character, const string& characterName) {
    Board& board = currentLevel->getBoard();
    int x = character.getX();
    int y = character.getY();

    if (board.isNearHealthBox(x, y)) {
        character.heal(10);
        board.removeHealthBox(x, y);
        cout << characterName << " found a health box! +10 Health!\n";
        logger.logMessage(characterName + " gained 10 health from health box");
    }

    if (board.isOnBombBox(x, y)) {
        if (characterName == "Player") {
            currentLevel->getEnemy().takeDamage(10);
            cout << "Player stepped on a bomb! Enemy takes 10 damage!\n";
            logger.logMessage("Player stepped on bomb - Enemy took 10 damage");
        }
        else {
            player.takeDamage(10);
            cout << "Enemy stepped on a bomb! Player takes 10 damage!\n";
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
        cout << "\n--- Player Turn ---\n";
        playerTurn();

        if (!currentLevel->getEnemy().isAlive()) break;
        if (!player.isAlive()) break;

        cout << "\n--- Enemy Turn (Player 2) ---\n";
        enemyTurn();

        if (!player.isAlive()) break;
        if (!currentLevel->getEnemy().isAlive()) break;

        currentLevel->getBoard().displayBoard(
            player.getX(), player.getY(),
            currentLevel->getEnemy().getX(), currentLevel->getEnemy().getY()
        );

        cout << "Player Health: " << player.getHealth()
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

    cout << "Player Position: " << player.getPosition() << "\n";
    cout << "Enemy Position: " << currentLevel->getEnemy().getPosition() << "\n";

    bool validMove = false;
    while (!validMove) {
        int newX, newY;
        cout << "Enter new X coordinate (0-9): ";
        cin >> newX;
        cout << "Enter new Y coordinate (0-9): ";
        cin >> newY;

        if (isValidMove(newX, newY, currentLevel->getEnemy())) {
            Character tempPlayer = player;
            tempPlayer.moveTo(newX, newY);
            if (tempPlayer.getDistanceTo(currentLevel->getEnemy()) >= 2) {
                player.moveTo(newX, newY);
                validMove = true;
                processSpecialBoxes(player, "Player");
            }
            else {
                cout << "You must stay at least 2 blocks away from the enemy!\n";
            }
        }
        else {
            cout << "Invalid move! Position occupied or out of bounds.\n";
        }
    }

    char choice;
    cout << "Attack enemy? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        if (player.attack(currentLevel->getEnemy())) {
            cout << "Player hits Enemy!\n";
        }
        else {
            cout << "Enemy is too far away to attack! (Max range: 3 blocks)\n";
        }
    }
}

void Game::enemyTurn() {
    cout << "Enemy Position: " << currentLevel->getEnemy().getPosition() << "\n";
    cout << "Player Position: " << player.getPosition() << "\n";

    bool validMove = false;
    while (!validMove) {
        int newX, newY;
        cout << "Enter new X coordinate for Enemy (0-9): ";
        cin >> newX;
        cout << "Enter new Y coordinate for Enemy (0-9): ";
        cin >> newY;

        if (isValidMove(newX, newY, player)) {
            Character tempEnemy = currentLevel->getEnemy();
            tempEnemy.moveTo(newX, newY);
            if (tempEnemy.getDistanceTo(player) >= 2) {
                currentLevel->getEnemy().moveTo(newX, newY);
                validMove = true;
                processSpecialBoxes(currentLevel->getEnemy(), "Enemy");
            }
            else {
                cout << "Enemy must stay at least 2 blocks away from the player!\n";
            }
        }
        else {
            cout << "Invalid move! Position occupied or out of bounds.\n";
        }
    }

    char choice;
    cout << "Attack player? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        if (currentLevel->getEnemy().attack(player)) {
            cout << "Enemy hits Player!\n";
        }
        else {
            cout << "Player is too far away to attack! (Max range: 3 blocks)\n";
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
            cout << "Level " << currentLevelNumber << " Cleared!\n";
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
        cout << "Congratulations! You won the game!\n";
    }
    else {
        cout << "Game Over. Try Again!\n";
    }
}

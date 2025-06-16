#include <iostream>
#include <ctime>
#include "Game.h"
#include "utils.h"

using namespace std;

int main()
{

    srand(static_cast<unsigned int>(time(0)));

    Game game;
    game.runGame();

    return 0;


}

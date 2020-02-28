#include <iostream>
#include "Funcs.h"
#include "Game.h"

using namespace std;

int main()
{
	/*srand(time(NULL));*/

	Game game;
	game.init();

	while (game.getIsRunning())
	{
		game.gameMenu();
	}

	system("PAUSE");

	return 0;
}

#include "Game.h"

using namespace std;

int main()
{
	// init game
	Game game;
	game.init();

	// keep running actual game menu until game is closed
	while (game.get_is_running())
	{
		game.game_Menu();
	}

	// prevent unwanted automatic exit
	system("PAUSE");

	return 0;
}

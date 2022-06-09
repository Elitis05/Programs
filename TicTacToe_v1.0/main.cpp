#include "Game.h"
#include "AiGame.h"

int selection = -1;

int main() {
	std::cout << "TicTacToe with GUI | Version 1.0\n\n"
		<< "Made by Seoul High School Computer Science Club\n\n";

	std::srand((unsigned int)time(NULL));

	while (selection != 0) {

	SELECT:
		std::cout << "Exit : 0 | PvP : 1 | PvE : 2\n\n";
		std::cin >> selection;
		std::cout << "\n";

		if (!(selection == 0 || selection == 1 || selection == 2)) {
			std::cout << "Error : Invalid input\n\n";
			goto SELECT;
		}
		
		if (selection == 1) {
			Game game;
			game.run();
		}
		if (selection == 2) {
			AiGame AIgame;
			AIgame.run();
		}

	}

	std::cout << "Thank you for playing!\n\n";
	//End of application
	return 0;
}
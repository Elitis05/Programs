#pragma once

#include "Board.h"
#include <iostream>
#include <sstream>

class Game
{
private:
	sf::RenderWindow* window;
	sf::Event e;

	sf::RectangleShape restartButton;

	//board
	Board* gameBoard;

	//text
	sf::Font font;
	sf::Text text;

	//game logic
	bool isPlayerTurn;//player = O, enemy = X
	int turn;
	bool gameEnded;

	//Mouse positions
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosWindow;

	void initFont();
	void initText();
	void initWindow();
	void initBoard();
	void initVar();
	
public:
	//Constructor, Destructor
	Game();
	virtual ~Game();

	//Functions
	void run();
	bool isWin();
	void gameEnd();
	void pollEvents();

	void updateTurn();

	void updateGUI(int winnerPlayer);
	void updateMousePosition();
	void updateBoard();//update if board is clicked
	void update();

	void renderGUI(sf::RenderTarget &target);
	void render();
};


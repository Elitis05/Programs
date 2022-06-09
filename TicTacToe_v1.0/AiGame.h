#pragma once

#include "Board.h"
#include <iostream>
#include <sstream>

class AiGame
{
private:
	sf::RenderWindow* window;
	sf::Event e;

	//board
	Board* gameBoard;

	//text
	sf::Font font;
	sf::Text text;

	//game logic
	bool isPlayerTurn;//player = O, enemy = X
	int turn;
	bool gameEnded;


	//AI variables
	std::vector<std::tuple<int, int, int>> bestResults;
	int searchCount;

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
	AiGame();
	virtual ~AiGame();

	//AI Functions
	std::pair<int,int> searchPos();//return best position
	std::tuple<int, int, int> findSelection(int nowTurn, bool nowIsPlayerTurn, Board& b);//minimax algorithm
	std::tuple<int, int, int> Maximize(int nowTurn, bool nowIsPlayerTurn, Board& b);
	std::tuple<int, int, int> Minimize(int nowTurn, bool nowIsPlayerTurn, Board& b);
	int evaluate(int turn, bool isPlayerTurn, Board &b);
	void printBestResults();

	//Functions
	void run();
	bool isWin();
	void gameEnd();
	void pollEvents();

	void updateTurn();

	void updateMousePosition();
	void updateBoard();//update if board is clicked
	void update();
	void render();
};


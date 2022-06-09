#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>

class Board
{
private:

	//Sprites
	sf::Sprite boardSprite;
	sf::Sprite squareSprites[3][3];

	//Textures
	sf::Texture boardTexture;
	sf::Texture xTexture;
	sf::Texture oTexture;

	sf::RectangleShape line;

	//board
	int** board;

	void initBoard();
	void initBoardTextures();
	void initBoardSprites();
	void initSideLine();//add line on the right

public:

	//Constructor, Destructor
	Board();
	Board(bool needRender);
	~Board();

	//Functions
	bool isWin();
	void fillBoardWithoutTexture(int shape, int x, int y);
	void fillBoard(int shape, int x, int y);//fill board  with X or O / shape 1 = O, 2 = X
	void emptySquare(int x, int y);
	const bool isEmpty(int x, int y) const;
	void printBoard();
	void copyBoard(Board &origin);

	void update();
	void render(sf::RenderTarget& target);
};


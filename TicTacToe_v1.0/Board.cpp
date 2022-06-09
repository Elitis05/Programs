#include "Board.h"

void Board::initBoard()
{
	this->board = new int *[3];
	for (int i = 0; i < 3; ++i)
		this->board[i] = new int[3];
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j)
			this->board[i][j] = 0;
	}
}

void Board::initBoardTextures()
{
	//Load textures from file
	if (!this->boardTexture.loadFromFile("Textures/TicTacToeBoard.png")) {
		std::cout << "Error : initBoardTexture() : board Texture : Failed to load texture from file\n";
	}
	if (!this->xTexture.loadFromFile("Textures/X.png")) {
		std::cout << "Error : initBoardTexture() : X Texture : Failed to load texture from file\n";
	}
	if (!this->oTexture.loadFromFile("Textures/O.png")) {
		std::cout << "Error : initBoardTexture() : O Texture : Failed to load texture from file\n";//scale 0.75f, 0.75f
	}
}

void Board::initBoardSprites()
{
	//Set the texture to the sprite
	this->boardSprite.setTexture(this->boardTexture);

	//Resize the sprite
	this->boardSprite.scale(1.5f, 1.5f);

	//set each square sprites' position
	float pos[3] = { 10.0, 196.0, 378.0};
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) 
			this->squareSprites[i][j].setPosition(pos[i], pos[j]);
	}
}

void Board::initSideLine()
{
	this->line.setFillColor(sf::Color::Black);
	this->line.setSize(sf::Vector2f(2.f, 540.f));
	this->line.setPosition(540.f, 0.f);
}

Board::Board()
{
	this->initBoard();
	this->initBoardTextures();
	this->initBoardSprites();
	this->initSideLine();
}

Board::Board(bool needRender)
{
	this->initBoard();
}

Board::~Board()
{
	for (int i = 0; i < 3; ++i)
		delete[] board[i];
	delete[] board;
}

bool Board::isWin()
{
	for (int i = 0; i < 3; ++i) {
		if (this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0)
			return true;
		if (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)
			return true;
	}
	if (this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0)
		return true;
	if (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[2][0] != 0)
		return true;
	return false;
}

void Board::fillBoardWithoutTexture(int shape, int x, int y)
{
	this->board[y][x] = shape;
}

void Board::fillBoard(int shape, int x, int y)
{
	//fill board  with X or O / shape 1 = O, 2 = X
	this->board[y][x] = shape;
	if (shape == 1) {
		this->squareSprites[x][y].setTexture(this->xTexture);
		this->squareSprites[x][y].setScale(150.f / this->xTexture.getSize().x, 150.f / this->xTexture.getSize().y);
	}
	else if (shape == 2) {
		this->squareSprites[x][y].setTexture(this->oTexture);
		this->squareSprites[x][y].setScale(150.f / this->oTexture.getSize().x, 150.f / this->oTexture.getSize().y);
	}
}

void Board::emptySquare(int x, int y)
{
	this->board[y][x] = 0;
}

const bool Board::isEmpty(int x, int y) const
{
	return this->board[y][x] == 0;
}

void Board::printBoard()
{
	std::cout << "\n";
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j)
			std::cout << this->board[i][j] << " ";
		std::cout << "\n";
	}
	std::cout << "\n";
}

void Board::copyBoard(Board & origin)
{
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j)
			this->board[i][j] = origin.board[i][j];
	}
}

void Board::update()
{

}

void Board::render(sf::RenderTarget& target)
{	
	target.draw(this->line);
	target.draw(this->boardSprite);

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			target.draw(this->squareSprites[i][j]);
		}
	}
}
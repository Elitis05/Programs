#include "Game.h"

void Game::initFont()
{
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf")) {
		std::cout << "Font loading error\n";
	}
}

void Game::initText()
{
	this->text.setFont(this->font);
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800,540), "TicTacToe (PvP)", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	//this->window->setVerticalSyncEnabled(false);
}

void Game::initBoard()
{
	this->gameBoard = new Board();
}

void Game::initVar()
{
	this->isPlayerTurn = true;
	this->turn = 1;
	this->gameEnded = false;
}

Game::Game()
{
	this->initBoard();
	this->initVar();
	this->initFont();
	this->initText();
}

Game::~Game()
{
	delete this->window;
	delete this->gameBoard;
}

void Game::run()
{
	this->initWindow();

	std::cout << "Turn : " << this->turn << "\n";

	while (this->window->isOpen()) {

		this->pollEvents();

		if (gameEnded == false)//stop updating if game ended
			this->update();
			
		this->render();
	}
}

bool Game::isWin()
{
	return this->gameBoard->isWin();
}

void Game::gameEnd()
{
	/*
	End Game if someone wins or tie
	Nothing happen if still playing
	*/
	if (this->isWin()) {
		if (this->isPlayerTurn) {
			std::cout << "Player 1 Win!\n\n";
		}
		else
			std::cout << "Player 2 Win!\n\n";
		this->gameEnded = true;
	}
	else if (this->turn == 9) {
		std::cout << "Tie!\n\n";
		this->gameEnded = true;
	}
	if (gameEnded == true)
		std::cout << "------------------------------------\nClose window to go back to initial screen\n------------------------------------\n\n";
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->e)) {
		switch (this->e.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		}
	}
}

void Game::updateTurn()
{
	this->gameBoard->printBoard();

	//check if game ended
	this->gameEnd();

	//change turn
	this->isPlayerTurn = !this->isPlayerTurn;
	++this->turn;

	if (gameEnded == true)
		return;

	std::cout << "Turn : " << this->turn << "\n";
}

void Game::updateGUI(int winnerPlayer)
{
	std::stringstream ss;

	if (winnerPlayer == 1)
		ss << "Player1 win!";
	else if (winnerPlayer == 2)
		ss << "Player2 win!";

	this->text.setString(ss.str());
}

void Game::updateMousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition();
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);

	this->mousePosWindow.x -= 8 + window->getPosition().x;
	this->mousePosWindow.y -= 30 + window->getPosition().y;

	//std::cout << this->mousePosWindow.x << " " << this->mousePosWindow.y << "\n";
}

void Game::updateBoard()
{
	int boardX, boardY;

	//Clicked on square
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if ((0 <= this->mousePosWindow.x && this->mousePosWindow.x < 540) && (0 <= this->mousePosWindow.y && this->mousePosWindow.y < 540)) {

			boardX = this->mousePosWindow.x / 180;
			boardY = this->mousePosWindow.y / 180;

			if (this->gameBoard->isEmpty(boardX, boardY)) {

				//fill board with shape
				this->gameBoard->fillBoard(this->isPlayerTurn + 1, boardX, boardY);

				//change turn
				this->updateTurn();
			}
		}
	}
}

void Game::update()
{
	this->updateMousePosition();

	this->updateBoard();
}

void Game::renderGUI(sf::RenderTarget &target)
{
	target.draw(this->text);
}

void Game::render()
{
	this->window->clear(sf::Color::White);

	//Display
	this->gameBoard->render(*this->window);

	this->renderGUI(*this->window);

	this->window->display();
}

#include "AiGame.h"

void AiGame::initFont()
{
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf")) {
		std::cout << "Font loading error\n";
	}
}

void AiGame::initText()
{
	this->text.setFont(this->font);
}

void AiGame::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 540), "TicTacToe with AI", sf::Style::Close | sf::Style::Titlebar);
	//this->window->setFramerateLimit(144);
	//this->window->setVerticalSyncEnabled(false);
}

void AiGame::initBoard()
{
	this->gameBoard = new Board();
}

void AiGame::initVar()
{
	this->isPlayerTurn = true;
	this->turn = 1;
	this->gameEnded = false;
	this->searchCount = 0;
}

AiGame::AiGame()
{
	this->initBoard();
	this->initVar();
}

AiGame::~AiGame()
{
	delete this->window;
	delete this->gameBoard;
}

 std::pair<int,int> AiGame::searchPos()
{
	 int value;
	 std::pair<int, int> pos;
	 this->searchCount = 0;

	 std::tie(pos.first, pos.second, value) = findSelection(this->turn, this->isPlayerTurn, *this->gameBoard);

	 this->printBestResults();

	 return pos;
}

std::tuple<int, int, int> AiGame::findSelection(int nowTurn, bool nowIsPlayerTurn, Board& b)
{
	/*
	Based on Minimax Algorithm

	@return Xpos, Ypos, Evaluation value

	*/

	++this->searchCount;

	//printf("%d\n", searchCount);

	if (nowTurn == 10)
		return { 0,0,evaluate(nowTurn, nowIsPlayerTurn, b) };

	if (nowIsPlayerTurn == true)
		return Minimize(nowTurn, nowIsPlayerTurn, b);

	else
		return Maximize(nowTurn, nowIsPlayerTurn, b);
}

std::tuple<int, int, int> AiGame::Maximize(int nowTurn, bool nowIsPlayerTurn, Board & b)
{
	Board newBoard(false);
	std::pair<int, int> tmpPos, bestPos;
	int tmpEval = 0, bestEval = 0;
	std::vector<std::tuple<int, int, int>> bestSelections;

	bestEval = -1000;
	newBoard.copyBoard(b);

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {

			if (b.isEmpty(i, j)) {

				newBoard.fillBoardWithoutTexture(nowIsPlayerTurn + 1, i, j);

				tmpEval = evaluate(nowTurn, nowIsPlayerTurn, newBoard);

				//newBoard.printBoard();

				if (tmpEval == 0)
					std::tie(tmpPos.first, tmpPos.second, tmpEval) = findSelection(nowTurn + 1, !nowIsPlayerTurn, newBoard);

				else {//if game ends next turn
					tmpPos.first = i;
					tmpPos.second = j;
				}

				if (bestEval <= tmpEval) {//if AI's turn, select best one for AI
					if (bestEval < tmpEval) {
						bestEval = tmpEval;
						bestPos = { i,j };
						bestSelections.clear();
					}
					bestSelections.push_back({ bestPos.first, bestPos.second, bestEval });
				}

				newBoard.emptySquare(i, j);
			}

		}
	}

	if (nowTurn == this->turn) {
		for(int i=0;i<(int)bestSelections.size();++i)
			this->bestResults.push_back(bestSelections[i]);
	}

	return bestSelections[rand() % bestSelections.size()];  //return random position from best choices
}

std::tuple<int, int, int> AiGame::Minimize(int nowTurn, bool nowIsPlayerTurn, Board & b)
{
	Board newBoard(false);
	std::pair<int, int> tmpPos, bestPos;
	int tmpEval = 0, bestEval = 0;
	std::vector<std::tuple<int, int, int>> bestSelections;

	bestEval = 1000;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {

			if (b.isEmpty(i, j)) {

				newBoard.copyBoard(b);

				newBoard.fillBoardWithoutTexture(nowIsPlayerTurn + 1, i, j);

				tmpEval = evaluate(nowTurn, nowIsPlayerTurn, newBoard);

				//newBoard.printBoard();

				if (tmpEval == 0)//except tie
					std::tie(tmpPos.first, tmpPos.second, tmpEval) = findSelection(nowTurn + 1, !nowIsPlayerTurn, newBoard);

				else {//if game ends next turn
					tmpPos.first = i;
					tmpPos.second = j;
				}

				if (bestEval >= tmpEval) {//if AI's turn, select best one for AI
					if (bestEval > tmpEval) {
						bestEval = tmpEval;
						bestPos = { i,j };
						bestSelections.clear();
					}
					bestSelections.push_back({ bestPos.first, bestPos.second, bestEval });
				}
			}

		}
	}

	if (nowTurn == this->turn)
		this->bestResults = bestSelections;

	return bestSelections[rand() % bestSelections.size()];  //return random position from best choices
}

int AiGame::evaluate(int nowTurn, bool nowIsPlayerTurn, Board &b)
{
	if (b.isWin()) {
		if (nowIsPlayerTurn)
			return -1;
		else
			return 1;
	}
	return 0;
}

void AiGame::printBestResults()
{
	std::cout << "Best positions\n\n";

	for (int i = 0; i < std::min(3, (int)bestResults.size()); ++i) 
		std::cout << i + 1 << ". pos : (" << std::get<0>(bestResults[i]) << ", " << std::get<1>(bestResults[i]) << ") | value : " << std::get<2>(bestResults[i]) <<"\n";
	
	std::cout << "\n\n";
}

void AiGame::run()
{
	int order;

	SELECT:
	std::cout << "select 1P(first) or 2P(second) (1 or 2): ";
	std::cin >> order;

	if (!(order == 1 || order == 2)) {
		std::cout << "Error : Invalid Input\n\n";
		goto SELECT;
	}

	if (order == 1)
		this->isPlayerTurn = true;
	else
		this->isPlayerTurn = false;

	this->initWindow();

	this->render();

	std::cout << "Turn : " << this->turn << "\n";

	while (this->window->isOpen()) {

		this->pollEvents();

		if (gameEnded == false)//stop updating if Game ended
			this->update();

		this->render();
	}
}

bool AiGame::isWin()
{
	return this->gameBoard->isWin();
}

void AiGame::gameEnd()
{
	/*
	End AiGame if someone wins or tie
	Nothing happen if still playing
	*/
	if (this->isWin()) {
		if (this->isPlayerTurn) {
			std::cout << "Player Win!\n";
		}
		else
			std::cout << "AI Win!\n\n";
		this->gameEnded = true;
	}
	else if (this->turn == 9) {
		std::cout << "Tie!\n\n";
		this->gameEnded = true;
	}
	if (gameEnded == true)
		std::cout << "-----------------------------------------\nClose window to go back to initial screen\n-----------------------------------------\n\n";
}

void AiGame::pollEvents()
{
	while (this->window->pollEvent(this->e)) {
		switch (this->e.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		}
	}
}

void AiGame::updateTurn()
{
	this->gameBoard->printBoard();

	//check if AiGame ended
	this->gameEnd();

	//change turn
	this->isPlayerTurn = !this->isPlayerTurn;
	++this->turn;

	if (gameEnded == true)
		return;

	std::cout << "\nTurn : " << this->turn << "\n\n";
}

void AiGame::updateMousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition();
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);

	this->mousePosWindow.x -= 8 + window->getPosition().x;
	this->mousePosWindow.y -= 30 + window->getPosition().y;

	//std::cout << this->mousePosWindow.x << " " << this->mousePosWindow.y << "\n";
}

void AiGame::updateBoard()
{
	int boardX, boardY;

	//Clicked on square
	if (this->isPlayerTurn == true) {//Player's turn
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

	else if (this->isPlayerTurn == false) {//AI's turn

		std::pair<int, int> pos;
		pos = searchPos();

		std::cout << "Amount of Searched position : " << this->searchCount << "\n\n";

		bestResults.clear();

		this->gameBoard->fillBoard(this->isPlayerTurn + 1, pos.first, pos.second);

		this->updateTurn();
	}
}

void AiGame::update()
{
	this->updateMousePosition();

	this->updateBoard();
}

void AiGame::render()
{
	this->window->clear(sf::Color::White);

	//Display
	this->gameBoard->render(*this->window);

	this->window->display();
}

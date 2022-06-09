#include "board.h"

#include <stdio.h>

board::board(void) {
	Tboard = new char *[3];
	for (int i = 0; i < 3; ++i)
		Tboard[i] = new char[3];
	initBoard();
}

board::~board(void) {
	for (int i = 0; i < 3; ++i)
		delete[] Tboard[i];
	delete[] Tboard;
}

void board::initBoard()
{
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j)
			Tboard[i][j] = ' ';
	}
	turn = 1;
}

void board::copy(board &og) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j)
			Tboard[i][j] = og.Tboard[i][j];
	}
	nowPlayer = og.nowPlayer;
	turn = og.turn;
}

void board::playerSide(bool player) {
	nowPlayer = !player;
}

int board::getTurn() {
	return turn;
}

void board::put(int pos) {
	pos -= 1;
	if (nowPlayer == 0)
		Tboard[pos / 3][pos % 3] = 'X';
	else
		Tboard[pos / 3][pos % 3] = 'O';
}

bool board::canPut(int pos) {
	if (!(1 <= pos && pos <= 9))
		return false;
	pos -= 1;
	return Tboard[pos / 3][pos % 3] == ' ';
}

bool board::isWin() {
	char mark;
	if (nowPlayer == 0)
		mark = 'X';
	else
		mark = 'O';
	for (int i = 0; i < 3; ++i) {
		if (Tboard[i][0] == mark && Tboard[i][1] == mark && Tboard[i][2] == mark)
			return true;
		if (Tboard[0][i] == mark && Tboard[1][i] == mark && Tboard[2][i] == mark)
			return true;
	}
	if (Tboard[0][0] == mark && Tboard[1][1] == mark && Tboard[2][2] == mark)
		return true;
	if (Tboard[2][0] == mark && Tboard[1][1] == mark && Tboard[0][2] == mark)
		return true;
	return false;
}

bool board::gameEnd() {
	if (isWin() || isBoardFull())
		return true;
	return false;
}

bool board::isBoardFull() {
	return turn == 10;
}

bool board::getIsNowPlayer() {
	return nowPlayer;
}

void board::changeTurn() {
	nowPlayer = !nowPlayer;
	++turn;
}

void board::printBoard() {
	printf("\n\n");
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 2; ++j) {
			if (Tboard[i][j] == ' ')
				printf(" - ");
			else
				printf(" %c ", Tboard[i][j]);
		}
		if (Tboard[i][2] == ' ')
			printf(" -\n");
		else
			printf(" %c\n", Tboard[i][2]);
		if (i <= 1)
			printf("\n");
	}
	printf("\n\n");
}

bool board::posEmpty(int pos) {
	pos -= 1;
	if (Tboard[pos / 3][pos % 3] == ' ')
		return true;
	return false;
}
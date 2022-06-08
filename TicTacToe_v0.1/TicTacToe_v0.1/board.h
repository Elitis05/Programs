#pragma once

class board {
private:
	char **Tboard;
	int turn;
	bool nowPlayer;  //1이면 사람 0이면 AI

public:
	board(void);
	~board(void);
	void copy(board &og);
	void playerSide(bool player);
	int getTurn();
	void put(int pos);
	bool canPut(int pos);
	bool isWin();
	bool gameEnd();
	bool isBoardFull();
	bool getIsNowPlayer();  //지금 사람 턴이면 1, AI면 0
	void changeTurn();
	void printBoard();
	bool posEmpty(int pos);
};
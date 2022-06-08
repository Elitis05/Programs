#include "evaluate.h"

int evaluate(board& Board) {
	if (Board.getIsNowPlayer() == 1 && Board.isWin())//사람 승
		return -1;
	if (Board.getIsNowPlayer() == 0 && Board.isWin())//AI 승
		return 1;
	return 0;
}
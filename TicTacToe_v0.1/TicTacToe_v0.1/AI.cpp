#include "AI.h"

AI::AI(void) {
	searchCount = 0;
}

int AI::searchPos(board &main_Board) {
	int value = 0, pos = 0;
	std::tie(value, pos) = minimax(main_Board, main_Board.getTurn(), &searchCount);
	return pos;
}

int AI::getSearchCount() {
	return searchCount;
}

void AI::initSearchCount() {
	searchCount = 0;
}
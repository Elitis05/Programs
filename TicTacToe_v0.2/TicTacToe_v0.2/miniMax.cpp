#include "miniMax.h"

std::tuple<int, int> minimax(board& Board, int depth, int* searchCount) {
	++*searchCount;
	if (depth == 10)
		return std::make_tuple(evaluate(Board), 0);
	if (Board.getIsNowPlayer() == 1)
		return minimize(Board, depth, searchCount);
	else
		return maximize(Board, depth, searchCount);
}

std::tuple<int, int> minimize(board& Board, int depth, int* searchCount) {
	int min = 1000, miniMaxValue = 0, miniMaxPos = 0, minPos = 0, eval = 0;
	std::vector<std::tuple<int, int>> Minimums;  //min, minPos
	board newBoard;
	for (int i = 1; i <= 9; ++i) {
		if (Board.posEmpty(i)) {
			newBoard.copy(Board);
			newBoard.put(i);
			eval = evaluate(newBoard);
			newBoard.changeTurn();
			if (eval == 0)
				std::tie(miniMaxValue, miniMaxPos) = minimax(newBoard, depth + 1, searchCount);
			else
				miniMaxValue = eval;
			//printf("%d %d %d %d\n", depth, i, miniMaxValue, eval);
			if (miniMaxValue == min)
				Minimums.push_back({ miniMaxValue, i });
			if (miniMaxValue < min) {
				min = miniMaxValue;
				Minimums.clear();
				Minimums.push_back({ miniMaxValue, i });
			}
		}
	}
	srand((unsigned int)time(NULL));
	return Minimums[rand() % Minimums.size()];  //같은 평가치를 갖고 있는 선택지들 중 하나를 랜덤으로 반환
}

std::tuple<int, int> maximize(board& Board, int depth, int* searchCount) {
	int max = -1000, miniMaxValue = 0, miniMaxPos = 0, maxPos = 0, eval = 0;
	std::vector<std::tuple<int, int>> Maximums;
	board newBoard;
	for (int i = 1; i <= 9; ++i) {
		if (Board.posEmpty(i)) {
			newBoard.copy(Board);
			newBoard.put(i);
			eval = evaluate(newBoard);
			newBoard.changeTurn();
			if (eval == 0)
				std::tie(miniMaxValue, miniMaxPos) = minimax(newBoard, depth + 1, searchCount);
			else
				miniMaxValue = eval;
			//printf("%d %d %d %d\n", depth, i, miniMaxValue, eval);
			if (miniMaxValue == max)
				Maximums.push_back({ miniMaxValue, i });
			if (miniMaxValue > max) {
				max = miniMaxValue;
				Maximums.clear();
				Maximums.push_back({ miniMaxValue, i });
			}
		}
	}
	srand((unsigned int)time(NULL));
	return Maximums[rand() % Maximums.size()];
}

/*
0. minimax(board.turn)으로 시작

1. 비어있는 공간이 있으면 그곳 마킹후 minimax(depth + 1)

2. 깊이가 10이 되면 evaluate 함수 실행 및 반환 -> 노드의 가치가 매겨짐

3-1. board.nowPlayer == 0이면 maximize

3-2. board.nowPlayer == 1이면 minimize
*/
#pragma warning(disable:4996)

#include <stdio.h>

#include "AI.h"

board mainBoard;
AI gameAI;

void UI() {
	int whichSide;
	printf("select 1P(first) or 2P(second) : ");
	scanf("%d", &whichSide);
	mainBoard.playerSide(whichSide - 1);
	printf(" 1   2   3 \n\n 4   5   6 \n\n 7   8   9 \n");
}

void playGame() {
	int selectedPos;
	while (!mainBoard.gameEnd()) {
		mainBoard.printBoard();
		printf("Turn %d\n\n", mainBoard.getTurn());
		if (mainBoard.getIsNowPlayer() == 1) {  //사람 턴
			printf("It's your turn!\n");
			printf("Write a number to mark area : ");
			while (true) {
				scanf("%d", &selectedPos);
				if (mainBoard.canPut(selectedPos)) {
					mainBoard.put(selectedPos);
					break;
				}
				else
					printf("\nYou can't select this area\nWrite a number to mark area : ");
			}
			if (mainBoard.isWin()) {
				printf("\n");
				mainBoard.printBoard();
				printf("You win!\n");
				break;
			}
			mainBoard.changeTurn();
		}
		else {  //AI 턴
			printf("It's AI's turn\nAI is thinking...\n\n");
			mainBoard.put(gameAI.searchPos(mainBoard));
			printf("%d\n\n", gameAI.getSearchCount());
			gameAI.initSearchCount();
			if (mainBoard.isWin()) {
				printf("\n");
				mainBoard.printBoard();
				printf("AI win!\n");
				break;
			}
			mainBoard.changeTurn();
		}
		printf("\n\n");
	}
	if (!mainBoard.isWin()) {
		mainBoard.printBoard();
		printf("Tie!");
	}
}

int main() {
	UI();
	playGame();
	return 0;
}

/*

틱택토 게임

1. 내 진영 선택 -> AI는 상대쪽으로

2. 틱택토 보드 출력

 1 │ 2 │ 3 \n───╂───╂───\n 4 │ 5 │ 6 \n───╂───╂───\n 7 │ 8 │ 9 \n

3-1. 내 턴이면 숫자 입력해서 마크

3-2. AI 턴이면 minimax 알고리즘을 돌린 결과로 나온 최선의 결과들 중 하나를 선택

*/
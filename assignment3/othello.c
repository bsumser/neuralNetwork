#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef enum {White, Black, Empty} State; //define enum datatype for each square on the board

typedef struct gameBoard{ //struct contain the board, dynamically allocated array of State
	int boardSize; //base board size for game
	State **boardArray;
}gameBoard;

gameBoard initGameBoard(gameBoard othelloBoard, int s) {
	int boardSize = s;
	State **boardArray = malloc(s * sizeof *boardArray + (s * (s * sizeof **boardArray)));

	for (int i = 0; i <= s; i++)
		for (int j = 0; j <= s; j++)
				boardArray[i][j] = Empty;
}

int main() {
	int board = 0;	
	printf("welcome to othello, please enter the size of the board\n");
	scanf("%d", &board);
	
	return 0;
}

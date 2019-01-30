#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef enum {White, Black, Empty} State; //define enum datatype for each square on the board

typedef struct gameBoard{ //struct contain the board, dynamically allocated array of State
	int boardSize; //base board size for game
	State** boardArray;
}gameBoard;

gameBoard initGameBoard(gameBoard othelloBoard, int s) {
	othelloBoard.boardSize = s;
	othelloBoard.boardArray = (State**) calloc(othelloBoard.boardSize, sizeof(State*));

	for (int i = 0; i < othelloBoard.boardSize; i++ )
	{
			    othelloBoard.boardArray[i] = (State*) calloc(othelloBoard.boardSize, sizeof(State));
	}

	for (int i = 0; i < othelloBoard.boardSize; i++)
		for (int j = 0; j < othelloBoard.boardSize; j++){
				othelloBoard.boardArray[i][j] = Empty;
		}

}

void printBoard(gameBoard othelloBoard) {
	printf("printing out the board\n");
	for (int i = 0; i < othelloBoard.boardSize; i++)
		for (int j = 0; j < othelloBoard.boardSize; j++) {
				if (othelloBoard.boardArray[i][j] == White)
						printf("W");
				if (othelloBoard.boardArray[i][j] == Black)
						printf("B");
				if (othelloBoard.boardArray[i][j] == Empty)
						printf(".");
		}
}

int main() {
	gameBoard othello;
	int board;	
	printf("welcome to othello, please enter the size of the board\n");
	scanf("%d", &board);

	initGameBoard(othello, board);

	printBoard(othello);
	
	return 0;
}

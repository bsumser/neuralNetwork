#include <stdio.h>
#include <stdbool.h>

typedef enum state {White, Black, Full} State; //define enum datatype for each square on the board

typedef struct board { //struct contain the board, dynamically allocated array of State
	int boardSize = 12; //base board size for game
	State* boardArray = (State*)malloc(boardSize * boardSize * sizeof(State));
}gameBoard;

int main() {
	int board = 0;	
	printf("welcome to othello, please enter the size of the board\n");
	scanf("%d", &board);
	
	return 0;
}
